#include "stdafx.h"
#include "MessageWork.h"

String^ MessageWork::GetStringFromByte(array<Byte>^ data, Int32 startIndex, Int32 length)
{
	return Encoding::ASCII->GetString(data,startIndex,length);
}
String^ MessageWork::GetStringWithLength(...array<String^>^ data)
{
	return String::Concat(MessageWork::ComputeLength(data),String::Concat(data));
}
Int32 MessageWork::GetDataLength(NetworkStream^ stream)
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
Int32 MessageWork::GetCmd(NetworkStream^ stream)
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

String^ MessageWork::LinkerMessage(Int32 cmd, String^ message)
{
	String^ rezultMessage = String::Concat(MessageWork::ComputeLength(CMD_WITH_DELIMETER(cmd),message,DELIMITER_SYMBOL),CMD_WITH_DELIMETER(cmd),message,DELIMITER_SYMBOL);
	return rezultMessage;
}

String^ MessageWork::LinkerMessage(Int32 cmd)
{
	return String::Concat(MessageWork::ComputeLength(CMD_WITH_DELIMETER(cmd)),CMD_WITH_DELIMETER(cmd));
}

void MessageWork::SendMessage(NetworkStream^ stream, String^ message)
{
	array<Byte>^ messageByte = Encoding::ASCII->GetBytes(message);
	stream->Write(messageByte,0,messageByte->Length);
}
String^ MessageWork::ReadMessage(NetworkStream^ stream, array<Byte>^ buffer, Int32 startIndex, Int32 length)
{
	if (length <= 0)
		return String::Empty;
	Array::Resize(buffer,startIndex+length);
	return GetStringFromByte(buffer,startIndex,stream->Read(buffer,startIndex,buffer->Length));
}
String^ MessageWork::ComputeLength(...array<String^>^ data)
{
	Int32 length = 0;
	for(Int32 i = 0; i < data->Length; i++)
		length += data[i]->Length;
	return String::Concat(Convert::ToString(length),DELIMITER_SYMBOL);
}