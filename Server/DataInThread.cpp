#include "stdafx.h"
#include "DataInThread.h"

void DataInThread::ViewBoxItemAdd(String^ text)
{
	//ListViewItem^ item;
	//item = gcnew ListViewItem(text,0);

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
	//onlineList->ItemDelete(index);
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

System::Void DataInThread::ClientProc(System::Void)
{
	String^ ip = ((IPEndPoint^)tcpConnect->Client->RemoteEndPoint)->Address->ToString();
	try
	{
		array<Byte>^ receivedBytes = gcnew array<Byte>(1024);
		stream->ReadTimeout = 1000;
		Int32 attempt = 0;
		/*while(!stream->DataAvailable)
		{
			Thread::Sleep(THREAD_TIMEOUT);
			attempt++;
			if(attempt == COUNT_ATTEMPT)
			{
				attempt = 0;
				return;
			}
		}*/
		
		/*Int32 length = MessageWork::GetDataLength(stream);
		Int32 cmd = MessageWork::GetCmd(stream);
		String^ receivedStr = MessageWork::ReadMessage(stream,receivedBytes,0,length-CMD_LENGTH-DELIMITER_LENGTH);
		String^ responseString = String::Empty;
		String^ login = String::Empty;
		String^ hash = String::Empty;*/
		SafeAddOnlineClientInList(((IPEndPoint^)tcpConnect->Client->RemoteEndPoint)->Address->ToString());
		while (1);
		Int32 cmd = 0x01;
		String^ responseString = String::Empty;
		String^ login = String::Empty;
		String^ hash = String::Empty;
		String^ receivedStr = String::Empty;
		switch (cmd)
		{
		/*case CMD::Registration:
			{
				login = MessageWork::ConvertLogin(receivedStr);
				if(base->AuthenticationResponse(receivedStr))
					MessageWork::SendMessage(stream, MessageWork::LinkerMessage(CMD::OK));
				else
					MessageWork::SendMessage(stream, MessageWork::LinkerMessage(CMD::Fail));
				break;
			}*/
		case CMD::Authentication:
			{
				//login = MessageWork::ConvertLogin(receivedStr);
				//hash  = MessageWork::ConvertHash(receivedStr);
				bool authFlag = true;
				//RecordBase^ recordAuth = gcnew RecordBase(login,hash);
				//Client^ currentClient = gcnew Client(tcpConnect,login);
				/*if(base->Contains(recordAuth) == true)
					if(onlineClientList->Add(currentClient) != -1)
					{
						MessageWork::SendMessage(currentClient->Stream, MessageWork::LinkerMessage(CMD::OK));
						authFlag = true;
					}
					else
						MessageWork::SendMessage(currentClient->Stream, MessageWork::LinkerMessage(CMD::Fail));
				else
					MessageWork::SendMessage(currentClient->Stream, MessageWork::LinkerMessage(CMD::Fail));*/
				if(authFlag == true)
				{
					//friendBase = gcnew FriendBase(login);
					
					stream->ReadTimeout = READ_TIMEOUT;
					while(1)
					{
						try
						{
							Int32 attempt = 0;
							while(!stream->DataAvailable)
							{
								Thread::Sleep(THREAD_TIMEOUT);
								attempt++;
								if(attempt == COUNT_ATTEMPT)
								{
									attempt = 0;
									SafeViewBoxItemDelete(login);
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
									/*array<String^>^ copyBase = friendBase->ReturnAll();
									for(Int32 i = 0; i < copyBase->Length; i++)
									{
										copyBase[i] += DELIMITER_SYMBOL;
										if(onlineClientList->Contains(copyBase[i]->Substring(0,copyBase[i]->Length-1)))
											copyBase[i] += ONLINE_SYMBOL;
										else
											copyBase[i] += OFFLINE_SYMBOL;
										copyBase[i] += DELIMITER_SYMBOL;
									}
									String^ signMessage = MessageWork::LinkerMessage(CMD::ReceivedFriendList,copyBase);
									MessageWork::SendMessage(currentClient->Stream, signMessage);*/
									break;
								}
							default:
								{
									throw gcnew Exception("Неизвестная команда");
									break;
								}
							}
						}	
						catch (ThreadAbortException^ thAbort)
						{
							SafeViewBoxItemDelete(login);
		
						}
						catch(Exception^ e)
						{
							MessageBox::Show(e->Message);
							SafeViewBoxItemDelete(login);
							return;
						}
					}
				}
				break;
			}
		default:
			break;
		}
	}
	catch (ThreadAbortException^ thAbort)
	{
		//SafeViewBoxItemDelete(ip);
		return;
	}
	catch(Exception^ e)
	{
		return;
	}
}