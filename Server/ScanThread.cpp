#include "stdafx.h"
#include "ScanThread.h"

void ScanThread::ViewBoxItemAdd(String^ text)
{
	//ListViewItem^ item;
	//item = gcnew ListViewItem(text,0);
	
	onlineList->Items->Add(text);
}
void ScanThread::SafeAddOnlineClientInList(String^ text)
{
	Action<String^>^ add = gcnew Action<String^>(this, &ScanThread::ViewBoxItemAdd);
	if(onlineList->InvokeRequired)
		onlineList->Invoke(add,text);
	else
		ViewBoxItemAdd(text);
}
void ScanThread::ViewBoxItemDelete(String^ text)
{
	for(Int32 i = 0; i < onlineList->Items->Count; i++)
		if(onlineList->Items[i]->ToString() == text)
			onlineList->Items->RemoveAt(i);
				
}
void ScanThread::SafeViewBoxItemDelete(String^ text)
{
	DeleteItem^ deleteItem;
	deleteItem = gcnew DeleteItem(this, &ScanThread::ViewBoxItemDelete);
	if(onlineList->InvokeRequired)
		onlineList->Invoke(deleteItem,text);
	else
		ViewBoxItemDelete(text);
}
void ScanThread::ViewBoxItemDelete(Int32 index)
{
	onlineList->Items->RemoveAt(index);		
	//onlineList->ItemDelete(index);
}
void ScanThread::SafeViewBoxItemDelete(Int32 index)
{
	DeleteItemIndex^ deleteItem;
	deleteItem = gcnew DeleteItemIndex(this, &ScanThread::ViewBoxItemDelete);
	if(onlineList->InvokeRequired)
		onlineList->Invoke(deleteItem,index);
	else
		ViewBoxItemDelete(index);
}
System::Void ScanThread::WriteTextInTextBox(TextBox^ textBox, String^ text) 
{
	textBox->Text = text;
}
System::Void ScanThread::SafeWriteTextInTextBox(TextBox^ textBox, String^ text)
{
	WriteText^ writeItem;
	writeItem = gcnew WriteText(this, &ScanThread::WriteTextInTextBox);
	if(onlineList->InvokeRequired)
		onlineList->Invoke(writeItem,textBox,text);
	else
		WriteTextInTextBox(textBox,text);
}
System::Void ScanThread::ClientProc(System::Void)
{
	UInt32 count_thread = 0;
	server->Start();
	try
	{
		while(1)
		{
			bool pend = server->Pending();
			threadCollection->CheckAlive();
			if(pend == true)
			{
				TcpClient^ tcpClient = server->AcceptTcpClient();
				Thread^ newClient;
				DataInThread^ data = gcnew DataInThread(tcpClient, onlineList);
				newClient = gcnew Thread(gcnew ThreadStart(data, &DataInThread::ClientProc));
				threadCollection->Add(newClient);
				newClient->Start();
			}
			//SafeWriteTextInTextBox(countClientBox, Convert::ToString(onlineClientCollection->Count));
			//SafeWriteTextInTextBox(countThreadBox, Convert::ToString(threadCollection->Count));
			
		}
	}
	catch(ThreadAbortException^ e)
	{
		threadCollection->RemoveAll();
		//onlineClientCollection->RemoveAll();
		//baseRecord->Clear();
		if(e->ExceptionState != "closeProgram")
		{
			Int32 itemsCount = onlineList->Items->Count;
			for(Int32 i = 0; i < itemsCount; i ++)
				SafeViewBoxItemDelete(0);
			server->Stop();
			//SafeWriteTextInTextBox(countClientBox, "Сервер остановлен");
			//SafeWriteTextInTextBox(countThreadBox, "Сервер остановлен");
		}
		return;
	}
	catch(Exception^ e)
	{
		server->Stop();
		return;
	}
}
