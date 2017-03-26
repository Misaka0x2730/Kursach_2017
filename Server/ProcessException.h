#pragma once

using namespace System;
using namespace System::ComponentModel;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;
using namespace System::Net;
using namespace System::Net::Sockets;
using namespace System::Threading;
using namespace System::Text;
using namespace System::Security::Cryptography;
using namespace System::Media;
using namespace System::Reflection;
using namespace System::Collections;

public ref class ProcessException abstract sealed
{
public:
	static System::Void MessageException(Exception^ e, System::Type^ type, String^ method);
	static System::Void MessageException(Exception^ e, String^ type, String^ method);
	static System::Void MessageException(String^ message, String^ target, String^ type, String^ method);
	static System::Void MessageException(Exception^ e, System::Type^ type, MethodBase^ method);
	static System::Void MessageException(Exception^ e, String^ type, MethodBase^ method);
};