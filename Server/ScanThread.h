#pragma once

#include "TcpParameter.h"
#include "ThreadsWork.h"
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
using namespace Server;

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
	Schedule^ schedule;
	System::Int16 port;

public:
	ScanThread(ListBox^ onlineList, Schedule^ schedule, System::Int16 port)
	{
		threadCollection = gcnew ThreadWork();
		this->onlineList = onlineList;
		this->schedule = schedule;
		this->port = port;
	}
	~ScanThread()
	{
		delete threadCollection;
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