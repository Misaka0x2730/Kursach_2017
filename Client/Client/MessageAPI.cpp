#include "stdafx.h"
#include "MessageWork.h"

String^ MessageAPI::GetStringFromByte(array<Byte>^ data, Int32 startIndex, Int32 length)
{
	return Encoding::ASCII->GetString(data,startIndex,length);
}
String^ MessageAPI::GetStringWithLength(...array<String^>^ data)
{
	return String::Concat(MessageAPI::ComputeLength(data),String::Concat(data));
}
Int32 MessageAPI::GetDataLength(NetworkStream^ stream)
{
	Int32 dataLength = 0;
	array<Byte>^ responseByte = gcnew array<Byte>(MAX_LENGTH_OF_LENGTH+DELIMITER_LENGTH);
	for(Int32 i = 0; (i < MAX_LENGTH_OF_LENGTH+DELIMITER_LENGTH); i++)
	{
		stream->Read(responseByte,i,1);
		if(Encoding::ASCII->GetString(responseByte,i,1) == DELIMITER_SYMBOL)
		{
			dataLength = Convert::ToInt32(Encoding::ASCII->GetString(responseByte,0,i));
			break;
		}
	}
	return dataLength;
}
Int32 MessageAPI::GetCmd(NetworkStream^ stream)
{
	Int32 cmd = CMD::ERROR;
	array<Byte>^ responseByte = gcnew array<Byte>(CMD_LENGTH+DELIMITER_LENGTH);
	for(Int32 i = 0; (i < CMD_LENGTH+DELIMITER_LENGTH); i++)
	{
		stream->Read(responseByte,i,1);
		if(Encoding::ASCII->GetString(responseByte,i,1) == DELIMITER_SYMBOL)
		{
			cmd = Convert::ToInt32(Encoding::ASCII->GetString(responseByte,0,i));
			break;
		}
	}
	return cmd;
}
String^ MessageAPI::ConvertLogin(String^ data)
{
	return data->Substring(0,data->IndexOf(DELIMITER_SYMBOL));
}
String^ MessageAPI::ConvertLogin(String^ data, Int32 startIndex)
{
	return data->Substring(startIndex,data->IndexOf(DELIMITER_SYMBOL,startIndex)-startIndex);
}
String^ MessageAPI::ConvertHash(String^ data)
{
	String^ login = ConvertLogin(data);
	return data->Substring(login->Length+DELIMITER_LENGTH,data->IndexOf(DELIMITER_SYMBOL,login->Length+DELIMITER_LENGTH)-login->Length-DELIMITER_LENGTH);
}
String^ MessageAPI::ConvertToStringMessage(String^ data)
{
	String^ login = ConvertLogin(data);
	return data->Substring(login->Length+DELIMITER_LENGTH,data->IndexOf(DELIMITER_SYMBOL,login->Length+DELIMITER_LENGTH)-login->Length-DELIMITER_LENGTH);
}
String^ MessageAPI::ConvertBetweenDelimiterString(String^ data)
{
	return data->Substring(0,data->IndexOf(DELIMITER_SYMBOL));
}
String^ MessageAPI::ConvertBetweenDelimiterString(String^ data,Int32 startIndex)
{
	return data->Substring(startIndex,data->IndexOf(DELIMITER_SYMBOL,startIndex)-startIndex);
}
String^ MessageAPI::LinkerMessage(String^ message, String^ login)
{
	String^ rezultMessage = String::Concat(MessageAPI::ComputeLength(CMD_WITH_DELIMETER(CMD::Message),login,DELIMITER_SYMBOL,message,DELIMITER_SYMBOL),CMD_WITH_DELIMETER(CMD::Message),login,DELIMITER_SYMBOL,message,DELIMITER_SYMBOL);
	return rezultMessage;
}
String^ MessageAPI::LinkerMessage(Int32 cmd, String^ message)
{
	String^ rezultMessage = String::Concat(MessageAPI::ComputeLength(CMD_WITH_DELIMETER(cmd),message,DELIMITER_SYMBOL),CMD_WITH_DELIMETER(cmd),message,DELIMITER_SYMBOL);
	return rezultMessage;
}
String^ MessageAPI::LinkerMessage(Int32 cmd, String^ message, String^ login)
{
	String^ rezultMessage = String::Concat(MessageAPI::ComputeLength(CMD_WITH_DELIMETER(cmd),login,DELIMITER_SYMBOL,message,DELIMITER_SYMBOL),CMD_WITH_DELIMETER(cmd),login,DELIMITER_SYMBOL,message,DELIMITER_SYMBOL);
	return rezultMessage;
}
String^ MessageAPI::LinkerMessage(Int32 cmd)
{
	return String::Concat(MessageAPI::ComputeLength(CMD_WITH_DELIMETER(cmd)),CMD_WITH_DELIMETER(cmd));
}
String^ MessageAPI::LinkerMessage(Int32 cmd, ...array<String^>^ message)
{
	String^ messageString = String::Empty;
	for(Int32 i = 0; i < message->Length; i++)
		messageString += message[i];
	return String::Concat(MessageAPI::ComputeLength(CMD_WITH_DELIMETER(cmd),Convert::ToString(message->Length),DELIMITER_SYMBOL,messageString,DELIMITER_SYMBOL),CMD_WITH_DELIMETER(cmd),Convert::ToString(message->Length),DELIMITER_SYMBOL,messageString,DELIMITER_SYMBOL);
}
void MessageAPI::SendMessage(NetworkStream^ stream, String^ message)
{
	array<Byte>^ messageByte = Encoding::ASCII->GetBytes(message);
	stream->Write(messageByte,0,messageByte->Length);
}
String^ MessageAPI::ReadMessage(NetworkStream^ stream, array<Byte>^ buffer, Int32 startIndex, Int32 length)
{
	Array::Resize(buffer,startIndex+length);
	return GetStringFromByte(buffer,startIndex,stream->Read(buffer,startIndex,buffer->Length));
}
String^ MessageAPI::ComputeLength(...array<String^>^ data)
{
	Int32 length = 0;
	for(Int32 i = 0; i < data->Length; i++)
		length += data[i]->Length;
	return String::Concat(Convert::ToString(length),DELIMITER_SYMBOL);
}