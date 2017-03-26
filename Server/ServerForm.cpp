#include "stdafx.h"
#include "ServerForm.h"

namespace Server
{
	System::Void ClientForm::ClientForm_Load(System::Object^  sender, System::EventArgs^  e)
	{
		threadScanData = gcnew ScanThread(listBox1);
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
					isStart = false;
					button1->Text = L"Сервер остановлен";
				}

		}
		catch (Exception^ e)
		{
			ProcessException::MessageException(e, this->GetType(), MethodInfo::GetCurrentMethod());
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
}

