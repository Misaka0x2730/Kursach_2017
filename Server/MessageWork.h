#pragma once
#include "CommandWork.h"
#include "TcpParameter.h"

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

public ref class MessageWork abstract sealed
{
public:
	static String^ GetStringFromByte(array<Byte>^ data, Int32 startIndex, Int32 length);
	static String^ GetStringWithLength(...array<String^>^ data);
	static Int32 GetDataLength(NetworkStream^ stream);
	static Int32 GetCmd(NetworkStream^ stream);
	static String^ ConvertLogin(String^ data);
	static String^ ConvertLogin(String^ data, Int32 startIndex);
	static String^ ConvertHash(String^ data);
	static String^ ConvertToStringMessage(String^ data);
	static String^ ConvertBetweenDelimiterString(String^ data);
	static String^ ConvertBetweenDelimiterString(String^ data,Int32 startIndex);
	static String^ LinkerMessage(String^ message, String^ login);
	static String^ LinkerMessage(Int32 cmd, String^ message);
	static String^ LinkerMessage(Int32 cmd, String^ message, String^ login);
	static String^ LinkerMessage(Int32 cmd, ...array<String^>^ message);
	static String^ LinkerMessage(Int32 cmd);
	static String^ ComputeLength(...array<String^>^ data);
	static void SendMessage(NetworkStream^ stream, String^ message);
	static String^ ReadMessage(NetworkStream^ stream, array<Byte>^ buffer, Int32 startIndex, Int32 length);
};
