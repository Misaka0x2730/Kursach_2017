#pragma once

#include "TcpParameter.h"
#include "MessageWork.h"
#include "SafeQueue.h"
#include "ProcessException.h"

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

public ref class DataInThread
{
private:
	TcpClient^ tcpConnect;
	NetworkStream^ stream;
	ListBox^ onlineList;
	delegate void AddItem(String^ text);
	delegate void DeleteItem(String^ text);
	delegate void DeleteItemIndex(Int32 index);
	delegate void WriteText(TextBox^ textBox, String^ text);

public:
	DataInThread(TcpClient^ tcpConnect, ListBox^ onlineList)
	{
		this->tcpConnect = tcpConnect;
		this->onlineList = onlineList;
		this->stream = tcpConnect->GetStream();
	}
	void ViewBoxItemAdd(String^ text);
	void SafeAddOnlineClientInList(String^ text);
	void ViewBoxItemDelete(String^ text);
	void SafeViewBoxItemDelete(String^ text);
	void ViewBoxItemDelete(Int32 index);
	void SafeViewBoxItemDelete(Int32 index);
	System::Void ClientProc(System::Void);
};
