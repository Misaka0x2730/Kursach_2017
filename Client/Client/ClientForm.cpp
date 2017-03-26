#include "stdafx.h"
#include "ClientForm.h"

namespace Client
{
	System::Void ClientForm::button1_Click(System::Object^  sender, System::EventArgs^  e)
	{
		TcpClient^ tcp = gcnew TcpClient();

		try
		{
			tcp->Connect(IPAddress::Parse(ipBox->Text), Convert::ToInt16(portBox->Text));

			String^ responseString = String::Empty;
			tcp->GetStream()->ReadTimeout = 1000;

			//array<Byte>^ hash = (gcnew SHA1Managed())->ComputeHash((gcnew UnicodeEncoding())->GetBytes(passwordBox->Text));
			//MessageAPI::SendMessage(tcp->GetStream(), MessageAPI::LinkerMessage(CMD::Authentication, BitConverter::ToString(hash, 0, hash->Length), loginBox->Text));

			//Int32 length = MessageAPI::GetDataLength(tcp->GetStream());
			//Int32 cmd = MessageAPI::GetCmd(tcp->GetStream());
			/*if (cmd == CMD::OK)
			{
				if (loginBox->Text == "Accelerator")
					MessageBox::Show("Nice to meet ya.", "I'm Accelerator.");
				IMMenu^ IMForm = gcnew IMMenu(this->Left, this->Top, tcp, loginBox->Text);
				this->Hide();
				this->AddOwnedForm(IMForm);
				Thread^ newClient;
				PersonalMessageWork^ data = gcnew PersonalMessageWork(tcp, loginBox->Text, IMForm);
				newClient = gcnew Thread(gcnew ThreadStart(data, &PersonalMessageWork::CentralProcess));
				newClient->Start();
				IMForm->Activate();
				IMForm->Show();
				IMForm->SetThread(newClient);
				IMForm->Text = loginBox->Text;
			}
			else
				MessageBox::Show("Неверный логин/пароль. Ну или Мисака вновь снесла всю базу данных. ");*/
		}
		catch (Exception^ e)
		{
			MessageBox::Show(e->Message, "Ошибка!");
		}
	}
}
