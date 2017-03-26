// Client.cpp: главный файл проекта.

#include "stdafx.h"
#include "ServerForm.h"

using namespace System;
using namespace System::Windows::Forms;
using namespace Server;

[STAThreadAttribute]
int main(array<System::String ^> ^args)
{
	
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

	ClientForm^ server = gcnew ClientForm();
	Application::Run(server);
	return 0;
}
