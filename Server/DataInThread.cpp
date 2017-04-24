#include "stdafx.h"
#include "DataInThread.h"

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Collections::Generic;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;
using namespace System::Net;
using namespace System::Net::Sockets;
using namespace System::Threading;
using namespace System::IO;
using namespace System::Reflection;
using namespace System::Text;

namespace Server
{
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
			while (1)
			{
				Int32 attempt = 0;

				while (!stream->DataAvailable)
				{
					Thread::Sleep(THREAD_TIMEOUT);
					attempt++;
					if (attempt == COUNT_ATTEMPT)
					{
						attempt = 0;
						SafeViewBoxItemDelete(ip);
						return;
					}
				}
				Int32 length = MessageWork::GetDataLength(stream);
				Int32 com = MessageWork::GetCmd(stream);
				receivedStr = MessageWork::ReadMessage(stream, receivedBytes, 0, length - CMD_LENGTH - DELIMITER_LENGTH);
				switch (com)
				{
				case CMD::Sign:
				{
					String^ message = String::Empty;
					if ((GetSchedule()->state == true) && (GetSchedule()->ip == ip))
					{
						DateTime^ nowTime = DateTime::Now;
						bool needWrite = true;
						if (File::Exists(ip + ".txt") == true)
						{
							array<String^>^ readStr = File::ReadAllLines(ip + ".txt");
							for (int i = 0; i < readStr->Length; i++)
							{
								if (readStr[i] != "")
								{
									int periodRead = Convert::ToInt32(readStr[i]->Substring(readStr[i]->IndexOf(";") + 1, readStr[i]->Length - readStr[i]->IndexOf(";") - 1));
									DateTime^ scheduleRead = DateTime::Parse(readStr[i]->Substring(0, readStr[i]->IndexOf(";")));
									if (nowTime->CompareTo(scheduleRead) >= 0)
									{
										needWrite = false;
										List<String^>^ tempArray = gcnew List<String^>(readStr);
										tempArray->RemoveAt(i);
										readStr = tempArray->ToArray();
										File::WriteAllLines(ip + ".txt", readStr);
									}
									else
										needWrite = true;

									if (needWrite == true)
									{
										message += readStr[i];
										message += DELIMITER_SYMBOL;
									}
								}
							}
							schedule->state = false;
							if (message != String::Empty)
							{
								MessageWork::SendMessage(stream, MessageWork::LinkerMessage(CMD::SendSchedule, message));
								//schedule->state = false;
								File::Delete(ip + ".txt");
							}
							else
							{

							}
						}
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
		catch (Exception^)
		{
			//SafeViewBoxItemDelete(ip);
			return;
		}
	}
}