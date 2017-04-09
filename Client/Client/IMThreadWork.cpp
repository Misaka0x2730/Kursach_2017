#include "stdafx.h"
#include "IMThreadWork.h"

namespace Client
{
	PersonalMessageWork::PersonalMessageWork(TcpClient^ client, ClientForm^ form)
	{
		this->client = client;
		this->stream = client->GetStream();
		this->form = form;
	}

	String^ PersonalMessageWork::ComputeLength(...array<String^>^ data)
	{
		Int32 length = 0;
		for (Int32 i = 0; i < data->Length; i++)
			length += Encoding::ASCII->GetBytes(data[i])->Length;
		return String::Concat(Convert::ToString(length), DELIMITER_SYMBOL);
	}

	String^ PersonalMessageWork::ReadSetting(String^ key)
	{
		readSettingsDelegate^ readSettings = gcnew readSettingsDelegate(form, &ClientForm::ReadSetting);
		if (form->InvokeRequired)
			return (String^)form->Invoke(readSettings, key);
		else
			return (String^)form->ReadSetting(key);
	}

	void PersonalMessageWork::AddUpdateSetting(String^ key, String^ value)
	{
		addUpdateSettingsDelegate^ addUpdateSettings = gcnew addUpdateSettingsDelegate(form, &ClientForm::AddUpdateSetting);
		if (form->InvokeRequired)
			form->Invoke(addUpdateSettings, key, value);
		else
			form->AddUpdateSetting(key, value);
	}

	void PersonalMessageWork::CentralProcess(void)
	{
		array<String^>^ userList = gcnew array<String^>(5);
		bool receiveSchedule = false;
		try
		{
			while (1)
			{
				Int32 attempt = 0;
				String^ message = String::Empty;

				Thread::Sleep(THREAD_TIMEOUT * 5);
				message = MessageAPI::LinkerMessage(CMD::Sign);
				if (receiveSchedule == true)
				{
					message = MessageAPI::LinkerMessage(CMD::OK);
					stream->Write(Encoding::ASCII->GetBytes(message), 0, Encoding::ASCII->GetBytes(message)->Length);
					receiveSchedule = false;
				}
				else
				{
					message = MessageAPI::LinkerMessage(CMD::Sign);
					stream->Write(Encoding::ASCII->GetBytes(message), 0, Encoding::ASCII->GetBytes(message)->Length);
				}
				while (!stream->DataAvailable)
				{
					Thread::Sleep(THREAD_TIMEOUT);
					attempt++;
					if (attempt == COUNT_ATTEMPT_READ)
					{
						attempt = 0;
						MessageBox::Show("Сервер разорвал соединение.");
						return;
					}
				}

				Int32 dataLength = MessageAPI::GetDataLength(stream);
				if (dataLength != 0)
				{
					Int32 cmd = MessageAPI::GetCmd(stream);
					array<Byte>^ responseByte = gcnew array<Byte>(dataLength);
					String^ receivedString = String::Empty;
					if (dataLength > (DELIMITER_LENGTH + CMD_LENGTH))
					{
						dataLength -= (DELIMITER_LENGTH + CMD_LENGTH);
						receivedString = MessageAPI::ReadMessage(stream, responseByte, 0, dataLength);
					}
					switch (cmd)
					{
					case CMD::OK:
					{

						break;
					}
					case CMD::SendSchedule:
					{
						String^ dateTimeStr = MessageAPI::ConvertBetweenDelimiterString(receivedString);
						String^ periodStr = MessageAPI::ConvertBetweenDelimiterString(receivedString, dateTimeStr->Length + 1);
						int period = Convert::ToInt16(periodStr);
						DateTime^ dateTime = DateTime::Parse(dateTimeStr);
						receiveSchedule = true;
						AddUpdateSetting("schedule", dateTimeStr);
						AddUpdateSetting("period", periodStr);
						break;
					}
					default:
					{
						return;
						break;
					}
					}
				}
				else
					throw gcnew Exception("Read few bytes");
			}
		}
		catch (ThreadAbortException^ thAbort)
		{
			return;
		}
		catch (Exception^ e)
		{
			MessageBox::Show("Сервер разорвал соединение.");
			return;
		}
		finally
		{

		}
	}
}
