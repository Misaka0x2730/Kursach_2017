#pragma once

#include "ProcessException.h"
#include "TcpParameter.h"
#include "ThreadsWork.h"
#include "DataInThread.h"

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;
using namespace System::Net;
using namespace System::Net::Sockets;
using namespace System::Threading;
using namespace System::IO;
using namespace System::Reflection;
using namespace System::Text;

public ref class ScanThread
{
private:
	delegate void AddItem(String^ text);
	delegate void DeleteItem(String^ text);
	delegate void DeleteItemIndex(Int32 index);
	delegate void WriteText(TextBox^ textBox, String^ text);

    ThreadWork^ threadCollection;
	TcpListener^ server;
	ListBox^ onlineList;
	//TextBox^ countClientBox;
	//TextBox^ countThreadBox;

public:
	ScanThread(ListBox^ onlineList)
	{
		try
		{
			threadCollection = gcnew ThreadWork();
			server = gcnew TcpListener(PORT);

			this->onlineList = onlineList;
			//this->countClientBox = countOnlineBox;
			//this->countThreadBox = countThreadBox;
		}
		catch(Exception^ e)
		{
			ProcessException::MessageException(e,this->GetType(),MethodInfo::GetCurrentMethod());
		}
	}
	~ScanThread()
	{
		delete threadCollection;
		//delete baseRecord;
	}
	void ViewBoxItemAdd(String^ text);
	void SafeAddOnlineClientInList(String^ text);
	void ViewBoxItemDelete(String^ text);
	void SafeViewBoxItemDelete(String^ text);
	void ViewBoxItemDelete(Int32 index);
	void SafeViewBoxItemDelete(Int32 index);
	System::Void WriteTextInTextBox(TextBox^ textBox, String^ text);
	System::Void SafeWriteTextInTextBox(TextBox^ textBox, String^ text);
	System::Void ClientProc(System::Void);
};