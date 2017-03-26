// Client.cpp: главный файл проекта.

#include "stdafx.h"
#include "ClientForm.h"

using namespace System;
using namespace System::Windows::Forms;
using namespace Client;

[STAThreadAttribute]
int main(array<System::String ^> ^args)
{

	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

	ClientForm^ client = gcnew ClientForm();
	Application::Run(client);
	return 0;
}
