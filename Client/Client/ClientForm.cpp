#include "stdafx.h"
#include "ClientForm.h"
#include "IMThreadWork.h"

namespace Client
{
	System::Void ClientForm::button1_Click(System::Object^  sender, System::EventArgs^  e)
	{
		TcpClient^ tcp = gcnew TcpClient();

		try
		{
			if ((newClient == nullptr) || (newClient->IsAlive == false))
			{
				tcp->Connect(IPAddress::Parse(ipBox->Text), Convert::ToInt16(portBox->Text));
				tcp->GetStream()->ReadTimeout = 1000;
				String^ responseString = String::Empty;

				PersonalMessageWork^ data = gcnew PersonalMessageWork(tcp);
				newClient = gcnew Thread(gcnew ThreadStart(data, &PersonalMessageWork::CentralProcess));
				newClient->Start();
			}
		}
		catch (Exception^ e)
		{
			MessageBox::Show(e->Message, "Îøèáêà!");
		}
	}
	System::Void ClientForm::clientForm_Closing(System::Object^  sender, System::Windows::Forms::FormClosingEventArgs^  e)
	{
		if ((newClient != nullptr)&&(newClient->IsAlive == true))
		{
			newClient->Abort();
		}
	}
}
