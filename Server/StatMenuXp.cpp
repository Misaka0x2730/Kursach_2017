
#include "StatMenuXp.h"

namespace ServerXp
	{
		System::Void StatMenuXp::StatMenu_Load(System::Object^  sender, System::EventArgs^  e)
		{
			threadScanData = gcnew ScanThread(onlineList, countOnlineBox, countThreadBox);
		}
	
		System::Void StatMenuXp::startServerButton_Click(System::Object^  sender, System::EventArgs^  e)
		{
			try
			{
				if((scanThread == nullptr)||(scanThread->IsAlive == false))
				{
					Thread^ currentThread = gcnew Thread(gcnew ThreadStart(threadScanData , &ScanThread::ClientProc));
					scanThread = currentThread;
					scanThread->Start();
				}
			}
			catch(Exception^ e)
			{
				ProcessException::MessageException(e,this->GetType(),MethodInfo::GetCurrentMethod());
				return;
			}
		}

		System::Void StatMenuXp::stopServerButton_Click(System::Object^  sender, System::EventArgs^  e)
		{
			try
			{
				if((scanThread != nullptr)&&(scanThread->IsAlive == true))
					scanThread->Abort();
			}
			catch(Exception^ e)
			{
				ProcessException::MessageException(e,this->GetType(),MethodInfo::GetCurrentMethod());
			}
		}

		System::Void StatMenuXp::StatMenu_Closing(System::Object^  sender, System::Windows::Forms::FormClosingEventArgs^  e)
		{
			this->FormClosing -= gcnew System::Windows::Forms::FormClosingEventHandler(this, &StatMenuXp::StatMenu_Closing);
			if((scanThread != nullptr)&&(scanThread->IsAlive == true))
				scanThread->Abort("closeProgram");
			delete threadScanData;
			this->Owner->Close();
		}
	}
