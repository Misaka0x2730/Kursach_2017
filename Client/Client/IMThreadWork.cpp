#include "stdafx.h"
#include "IMThreadWork.h"

	PersonalMessageWork::PersonalMessageWork(TcpClient^ client)
	{
		this->client = client;
		this->stream = client->GetStream();
	}
	PersonalMessageWork::~PersonalMessageWork()
	{

	}

	String^ PersonalMessageWork::ComputeLength(...array<String^>^ data)
	{
		Int32 length = 0;
		for (Int32 i = 0; i < data->Length; i++)
			length += Encoding::ASCII->GetBytes(data[i])->Length;
		return String::Concat(Convert::ToString(length), DELIMITER_SYMBOL);
	}
	void PersonalMessageWork::AddUpdateSetting(String^ key, String^ value)
	{
		ConfigurationManager::OpenExeConfiguration(ConfigurationUserLevel::None);
		System::Configuration::Configuration^ configFile = ConfigurationManager::OpenExeConfiguration(ConfigurationUserLevel::None);
		System::Configuration::KeyValueConfigurationCollection^ settings = configFile->AppSettings->Settings;
		if (settings[key] == nullptr)
			settings->Add(key, value);
		else
			settings[key]->Value = value;

		configFile->Save(ConfigurationSaveMode::Modified);
		ConfigurationManager::RefreshSection(configFile->AppSettings->SectionInformation->Name);
	}
	String^ PersonalMessageWork::ReadSetting(String^ key)
	{
		System::Collections::Specialized::NameValueCollection^ appSettings = ConfigurationManager::AppSettings;
		String^ value = appSettings[key];
		if (value == nullptr)
			return String::Empty;
		else
			return value;
	}
	void PersonalMessageWork::CentralProcess(void)
	{
		array<String^>^ userList = gcnew array<String^>(5);
		bool receiveSchedule = false;
		try
		{
			while(1)
			{
				Int32 attempt = 0;
				String^ message = String::Empty;
				
				Thread::Sleep(THREAD_TIMEOUT*10);
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
				while(!stream->DataAvailable)
				{
					Thread::Sleep(THREAD_TIMEOUT);
					attempt++;
					if(attempt == COUNT_ATTEMPT_READ)
					{
						attempt = 0;
						MessageBox::Show("Сервер разорвал соединение.");
						//SafeSetCloseReason();
						//SafeCloseForm();
						return;
					}
				}

				Int32 dataLength = MessageAPI::GetDataLength(stream);
				if(dataLength != 0)
				{
					Int32 cmd = MessageAPI::GetCmd(stream);
					array<Byte>^ responseByte = gcnew array<Byte>(dataLength);
					String^ receivedString = String::Empty;
					if(dataLength > (DELIMITER_LENGTH+CMD_LENGTH))
					{
						dataLength -= (DELIMITER_LENGTH+CMD_LENGTH);
						receivedString = MessageAPI::ReadMessage(stream,responseByte,0,dataLength);
					}
					switch(cmd)
					{
						case CMD::OK:
						{

							break;
						}
						case CMD::SendSchedule:
						{
							String^ dateTimeStr = MessageAPI::ConvertBetweenDelimiterString(receivedString);
							String^ periodStr = MessageAPI::ConvertBetweenDelimiterString(receivedString, dateTimeStr->Length+1);
							int period = Convert::ToInt16(periodStr);
							DateTime^ dateTime = DateTime::Parse(dateTimeStr);
							receiveSchedule = true;
							MessageBox::Show("Получено расписание:" + Environment::NewLine + dateTimeStr + " период " + periodStr + " мин", "Получено расписание");
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
		catch(Exception^ e)
		{
			MessageBox::Show("Сервер разорвал соединение.");
			//SafeSetCloseReason();
			//SafeCloseForm();
			return;
		}
		finally
		{

		}
	}
