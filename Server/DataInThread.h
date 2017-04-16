#pragma once

#include "TcpParameter.h"
#include "MessageWork.h"

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

namespace Server
{
	public ref struct Schedule
	{
		DateTime^ dateTime;
		String^ ip;
		Int16 period;
		bool state;
	};

	public ref class DataInThread
	{
	private:
		TcpClient^ tcpConnect;
		NetworkStream^ stream;
		ListBox^ onlineList;
		Schedule^ schedule;
		delegate void AddItem(String^ text);
		delegate void DeleteItem(String^ text);
		delegate void DeleteItemIndex(Int32 index);
		delegate void WriteText(TextBox^ textBox, String^ text);
		delegate Schedule^ GetScheduleDelegate();

	public:
		DataInThread(TcpClient^ tcpConnect, ListBox^ onlineList, Schedule^ schedule)
		{
			this->tcpConnect = tcpConnect;
			this->onlineList = onlineList;
			this->stream = tcpConnect->GetStream();
			this->schedule = schedule;
		}
		void ViewBoxItemAdd(String^ text);
		void SafeAddOnlineClientInList(String^ text);
		void ViewBoxItemDelete(String^ text);
		void SafeViewBoxItemDelete(String^ text);
		void ViewBoxItemDelete(Int32 index);
		void SafeViewBoxItemDelete(Int32 index);
		Schedule^ GetSchedule();
		Schedule^ SafeGetSchedule();
		System::Void ClientProc(System::Void);
	};
}