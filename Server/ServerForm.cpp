#include "stdafx.h"
#include "ServerForm.h"

namespace Server
{
	System::Void ClientForm::ClientForm_Load(System::Object^  sender, System::EventArgs^  e)
	{
		//threadScanData = gcnew ScanThread(listBox1, schedule, Convert::ToInt16(textBox2));
	}

	System::Void ClientForm::startStopServerButton_Click(System::Object^  sender, System::EventArgs^  e)
	{
		static bool isStart = false;
		try
		{
			if (isStart == false)
			{
				if ((scanThread == nullptr) || (scanThread->IsAlive == false))
				{
					threadScanData = gcnew ScanThread(listBox1, schedule, Convert::ToInt16(textBox2->Text));
					Thread^ currentThread = gcnew Thread(gcnew ThreadStart(threadScanData, &ScanThread::ClientProc));
					scanThread = currentThread;
					scanThread->Start();
					isStart = true;
					button1->Text = L"Сервер запущен";
				}
			}
			else
				if ((scanThread != nullptr) && (scanThread->IsAlive == true))
				{
					scanThread->Abort();
					delete threadScanData;
					isStart = false;
					button1->Text = L"Сервер остановлен";
				}
		}
		catch (Exception^ )
		{
			return;
		}
	}
	System::Void ClientForm::ClientForm_Closing(System::Object^  sender, System::Windows::Forms::FormClosingEventArgs^  e)
	{
		this->FormClosing -= gcnew System::Windows::Forms::FormClosingEventHandler(this, &ClientForm::ClientForm_Closing);
		if ((scanThread != nullptr) && (scanThread->IsAlive == true))
			scanThread->Abort("closeProgram");
		delete threadScanData;
		this->Close();
	}

	System::Void ClientForm::button2_Click(System::Object^  sender, System::EventArgs^  e)
	{
		Int16 period = 0;
		if ((listBox1->SelectedIndex != -1) && (schedule->state == false) && 
		   (Int16::TryParse(textBox3->Text, period) == true))
		{
			if (period < 2880)
			{
				schedule->state = true;
				schedule->dateTime = dateTimePicker1->Value;
				schedule->ip = Convert::ToString(listBox1->Items[listBox1->SelectedIndex]);
				schedule->period = period;
			}
		}
	}
}

