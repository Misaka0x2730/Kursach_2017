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
				if (File::Exists(Convert::ToString(listBox1->Items[listBox1->SelectedIndex]) + ".txt") == false)
				{
					StreamWriter^ writeFile = gcnew StreamWriter(Convert::ToString(listBox1->Items[listBox1->SelectedIndex]) + ".txt");
					writeFile->WriteLine(dateTimePicker1->Value.ToString() + ";" + Convert::ToString(period));
					writeFile->Close();
				}
				else
				{
					String^ ip = Convert::ToString(listBox1->Items[listBox1->SelectedIndex]);
					array<String^>^ readStr = File::ReadAllLines(Convert::ToString(listBox1->Items[listBox1->SelectedIndex]) + ".txt");
					bool needWrite = true;
					DateTime^ nowTime = DateTime::Now;
					if (nowTime->CompareTo(dateTimePicker1->Value) < 0)
					{
						for (int i = 0; i < readStr->Length; i++)
						{
							if (readStr[i] != "")
							{
								int periodRead = Convert::ToInt32(readStr[i]->Substring(readStr[i]->IndexOf(";") + 1, readStr[i]->Length - readStr[i]->IndexOf(";") - 1));
								DateTime^ scheduleRead = DateTime::Parse(readStr[i]->Substring(0, readStr[i]->IndexOf(";")));
								if (dateTimePicker1->Value.CompareTo(scheduleRead) >= 0)
								{
									if (dateTimePicker1->Value.CompareTo(scheduleRead->AddMinutes(periodRead)) <= 0)
									{
										needWrite = false;
										break;
									}
									else
										needWrite = true;
								}
								else
								{
									if ((dateTimePicker1->Value.AddMinutes(period)).CompareTo(scheduleRead) >= 0)
									{
										needWrite = false;
										break;
									}
									else
										needWrite = true;
								}
							}
						}
						if (needWrite == true)
						{
							File::AppendAllText(Convert::ToString(listBox1->Items[listBox1->SelectedIndex]) + ".txt", Environment::NewLine + dateTimePicker1->Value.ToString() + ";" + Convert::ToString(period));
							listBox1_SelectedIndexChanged((System::Object^)listBox1, nullptr);
						}
					}
				}
			}
		}
	}
	System::Void ClientForm::button3_Click(System::Object^  sender, System::EventArgs^  e)
	{
		schedule->state = true; 
		schedule->ip = Convert::ToString(listBox1->Items[listBox1->SelectedIndex]);
		listBox1_SelectedIndexChanged((System::Object^)listBox1, nullptr);
	}
	System::Void ClientForm::listBox1_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e)
	{
		if ((listBox1->SelectedIndex != -1) && File::Exists(Convert::ToString(listBox1->Items[listBox1->SelectedIndex]) + ".txt") == true)
		{
			array<String^>^ readStr = File::ReadAllLines(Convert::ToString(listBox1->Items[listBox1->SelectedIndex]) + ".txt");
			textBox1->Text = String::Empty;
			for (int i = 0; i < readStr->Length; i++)
			{
				if(readStr[i] != "")
					textBox1->Text += (readStr[i]->Substring(0, readStr[i]->IndexOf(";")) + "  " + readStr[i]->Substring(readStr[i]->IndexOf(";") + 1, readStr[i]->Length - readStr[i]->IndexOf(";") - 1) + Environment::NewLine);
			}
		}
	}
}

