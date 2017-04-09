#include "stdafx.h"
#include "DataInThread.h"

void DataInThread::ViewBoxItemAdd(String^ text)
{
	onlineList->Items->Add(text);
}

void DataInThread::SafeAddOnlineClientInList(String^ text)
{
	Action<String^>^ add = gcnew Action<String^>(this, &DataInThread::ViewBoxItemAdd);
	if (onlineList->InvokeRequired)
		onlineList->Invoke(add, text);
	else
		ViewBoxItemAdd(text);
}

void DataInThread::ViewBoxItemDelete(String^ text)
{
	for (Int32 i = 0; i < onlineList->Items->Count; i++)
		if (onlineList->Items[i]->ToString() == text)
		{
			onlineList->Items->RemoveAt(i);
			return;
		}
}

void DataInThread::SafeViewBoxItemDelete(String^ text)
{
	DeleteItem^ deleteItem;
	deleteItem = gcnew DeleteItem(this, &DataInThread::ViewBoxItemDelete);
	if (onlineList->InvokeRequired)
		onlineList->Invoke(deleteItem, text);
	else
		ViewBoxItemDelete(text);
}

void DataInThread::ViewBoxItemDelete(Int32 index)
{
	onlineList->Items->RemoveAt(index);
}

void DataInThread::SafeViewBoxItemDelete(Int32 index)
{
	DeleteItemIndex^ deleteItem;
	deleteItem = gcnew DeleteItemIndex(this, &DataInThread::ViewBoxItemDelete);
	if (onlineList->InvokeRequired)
		onlineList->Invoke(deleteItem, index);
	else
		ViewBoxItemDelete(index);
}

Schedule^ DataInThread::GetSchedule()
{
	return schedule;
}

Schedule^ DataInThread::SafeGetSchedule()
{
	GetScheduleDelegate^ getSchedule = gcnew GetScheduleDelegate(this, &DataInThread::GetSchedule);
	if (onlineList->InvokeRequired)
		return (Schedule^)onlineList->Invoke(getSchedule);
	else
		return (Schedule^)GetSchedule();
}

System::Void DataInThread::ClientProc(System::Void)
{
	String^ ip = ((IPEndPoint^)tcpConnect->Client->RemoteEndPoint)->Address->ToString();
	try
	{
		SafeAddOnlineClientInList(((IPEndPoint^)tcpConnect->Client->RemoteEndPoint)->Address->ToString());

		array<Byte>^ receivedBytes = gcnew array<Byte>(1024);
		stream->ReadTimeout = 1000;
		
		Int32 cmd = 0x01;
		String^ responseString = String::Empty;
		String^ login = String::Empty;
		String^ hash = String::Empty;
		String^ receivedStr = String::Empty;

		stream->ReadTimeout = READ_TIMEOUT;
		while(1)
		{
			Int32 attempt = 0;

			while(!stream->DataAvailable)
			{
				Thread::Sleep(THREAD_TIMEOUT);
				attempt++;
				if(attempt == COUNT_ATTEMPT)
				{
					attempt = 0;
					SafeViewBoxItemDelete(ip);
					return;
				}
			}
			Int32 length = MessageWork::GetDataLength(stream);
			Int32 com = MessageWork::GetCmd(stream);
			receivedStr = MessageWork::ReadMessage(stream,receivedBytes,0,length-CMD_LENGTH-DELIMITER_LENGTH);
			switch(com)
			{
			case CMD::Sign:
				{
					String^ message;
					if ((GetSchedule()->state == true) && (GetSchedule()->ip == ip))
					{
						message = schedule->dateTime->ToString();
						message += DELIMITER_SYMBOL;
						message += schedule->period.ToString();
						MessageWork::SendMessage(stream, MessageWork::LinkerMessage(CMD::SendSchedule, message));
						schedule->state = false;
					}
					else
						MessageWork::SendMessage(stream, MessageWork::LinkerMessage(CMD::OK));
					break;
				}
			case CMD::OK:
			{
				MessageWork::SendMessage(stream, MessageWork::LinkerMessage(CMD::OK));
				break;
			}
			default:
				{
					throw gcnew Exception("Неизвестная команда");
					break;
				}
			}
		}
	}
	catch(Exception^ )
	{
		return;
	}
}