#include "stdafx.h"
#include "ClientForm.h"
#include "IMThreadWork.h"

namespace Client
{
	System::Void ClientForm::button1_Click(System::Object^  sender, System::EventArgs^  e)
	{
		TcpClient^ tcp = gcnew TcpClient();
		IPAddress^ ip;
		Int16 port;
		try
		{
			if (((newClient == nullptr) || (newClient->IsAlive == false)) &&
				(IPAddress::TryParse(ipBox->Text, ip) == true) && 
				(Int16::TryParse(portBox->Text, port) == true))
			{
				AddUpdateSetting("serverIP", ipBox->Text);
				AddUpdateSetting("serverPort", portBox->Text);
				tcp->Connect(IPAddress::Parse(ipBox->Text), Convert::ToInt16(portBox->Text));
				tcp->GetStream()->ReadTimeout = 1000;
				String^ responseString = String::Empty;

				PersonalMessageWork^ data = gcnew PersonalMessageWork(tcp, this);
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

	System::Void ClientForm::timer1_Tick(System::Object^  sender, System::EventArgs^  e)
	{
		String^ scheduleStr = ReadSetting("schedule");
		String^ periodStr = ReadSetting("period");
		if ((ReadSetting("schedule") != String::Empty) && (ReadSetting("period") != String::Empty))
		{
			DateTime^ nowDateTime = DateTime::Now;
			DateTime^ schedule = DateTime::Parse(scheduleStr);
			if ((nowDateTime->CompareTo(schedule) > 0) && 
				(nowDateTime->CompareTo(schedule->AddMinutes(Convert::ToInt16(periodStr))) < 0))
			{
				NetworkChangeState(false);
			}
			else
			{
				NetworkChangeState(true);
				if (nowDateTime->CompareTo(schedule->AddMinutes(Convert::ToInt16(periodStr))) > 0)
				{
					AddUpdateSetting("schedule", String::Empty);
					AddUpdateSetting("period", String::Empty);
				}
			}
		}
	}
}
