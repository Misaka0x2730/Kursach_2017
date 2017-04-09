#pragma once

#include "TcpParameter.h"
#include "MessageWork.h"
#include "ClientForm.h"

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;
using namespace System::Net;
using namespace System::Net::Sockets;
using namespace System::Security::Cryptography;
using namespace System::Text;
using namespace System::Media;
using namespace System::Configuration;
//using namespace Client;

namespace Client
{
	delegate bool getMessageState(void);
	delegate String^ getLoginMessage(void);
	delegate String^ getMessage(void);
	delegate void displayMessage(String^ login, String^ message);
	delegate bool getUpdateSearchList(void);
	delegate void resetUpdateSearchList(void);
	delegate String^ getSearchText(void);
	delegate String^ getNewFriendLogin(void);
	delegate Int32 getNewFriendState();
	delegate void resetNewFriendState();

	delegate String^ readSettingsDelegate(String^ key);
	delegate void addUpdateSettingsDelegate(String^ key, String^ value);

	public ref class PersonalMessageWork
	{
	private:
		String^ login;
		NetworkStream^ stream;
		TcpClient^ client;
		ClientForm^ form;
	public:
		PersonalMessageWork(TcpClient^ client, ClientForm^ form);
		void AddUpdateSetting(String^ key, String^ value);
		String^ ReadSetting(String^ key);
		String^ ComputeLength(...array<String^>^ data);
		void CentralProcess(void);
	};
}