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
			MessageBox::Show(e->Message, "Ошибка!");
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
		DateTime^ nowDateTime = DateTime::Now;
		DateTime^ schedule;
		bool networkState = true;
		bool scheduleLast = false;
		bool scheduleIsAccept = false;
		bool scheduleFlag = true;
		for (int i = 0; ReadSetting("schedule" + Convert::ToString(i)) != nullptr; i++)
		{
			if ((ReadSetting("period" + Convert::ToString(i)) == String::Empty) || (ReadSetting("schedule" + Convert::ToString(i)) == String::Empty))
				continue;
			
			scheduleIsAccept = true;
			schedule = DateTime::Parse(ReadSetting("schedule" + Convert::ToString(i)));

			if ((nowDateTime->CompareTo(schedule) > 0) &&
				(nowDateTime->CompareTo(schedule->AddMinutes(Convert::ToInt16(ReadSetting("period" + Convert::ToString(i))))) < 0))
			{
				NetworkChangeState(false);
				networkState = false;
				//break;
			}
			else
			{
				if (nowDateTime->CompareTo(schedule->AddMinutes(Convert::ToInt16(ReadSetting("period" + Convert::ToString(i))))) > 0)
				{
					AddUpdateSetting("schedule" + Convert::ToString(i), String::Empty);
					AddUpdateSetting("period" + Convert::ToString(i), String::Empty);
				}
			}

		}
		if ((ReadSetting("receivedSchedule") != nullptr) && (ReadSetting("receivedSchedule") == "1"))
		{
			scheduleLast = true;
			AddUpdateSetting("receivedSchedule", "0");
			MessageBox::Show("Получено расписание!");
		}
		if (networkState == true)
		{
			NetworkChangeState(true);
		}
	}
}
