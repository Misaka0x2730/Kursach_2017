#pragma once 

using namespace System;

enum CMD: UInt32
{
	ERROR = 0,
	OK = 1,
	Fail = 2,
	Registration = 3,
	Authentication = 4,
	Message = 5,
	Sign = 6,
	ReceivedFriendList = 7,
	GetSearchList = 8,
	SearchList = 9,
	AddNewFriend = 10,
	MessageNotDelivered = 11,
	SendSchedule = 12
};
public ref class CMD_STRING abstract sealed
{
public:
	static String^ GetCommandString(Int32 cmd)
	{
		switch (cmd)
		{
		case CMD::OK:
			{
				return "01";
				break;
			}
		case CMD::Fail:
			{
				return "02";
				break;
			}
		case CMD::Registration:
			{
				return "03";
				break;
			}
		case CMD::Authentication:
			{
				return "04";
				break;
			}
		case CMD::Message:
			{
				return "05";
				break;
			}
		case CMD::Sign:
			{
				return "06";
				break;
			}
		case CMD::ReceivedFriendList:
			{
				return "07";
				break;
			}
		case CMD::GetSearchList:
			{
				return "08";
				break;
			}
		case CMD::SearchList:
			{
				return "09";
				break;
			}
		case CMD::AddNewFriend:
			{
				return "10";
				break;
			}
		case CMD::MessageNotDelivered:
			{
				return "11";
				break;
			}
		case CMD::SendSchedule:
		{
			return "12";
			break;
		}
		default:
			return "00";
			break;
		}
	}
};

#define DELIMITER_SYMBOL ";"
#define END_SYMBOL "}"
#define DELIMITER_LENGTH 1
#define END_LENGTH 1
#define CMD_LENGTH 2
#define CMD_WITH_DELIMETER(cmd) String::Concat(CMD_STRING::GetCommandString(cmd),DELIMITER_SYMBOL)
#define MAX_LENGTH_OF_LENGTH 8
#define ONLINE_SYMBOL "1"
#define OFFLINE_SYMBOL "0"