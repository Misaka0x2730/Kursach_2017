#pragma once

using namespace System;

#define SETTINGS_FILE "settings.txt"

#define IP_LOCALHOST "127.0.0.1"
#define PORT_DEFAULT 10032

#define COUNT_ATTEMPT_READ 100
#define THREAD_TIMEOUT 20 

#define DELIMITER_SYMBOL ";"
#define DELIMITER_LENGTH 1
#define CMD_LENGTH 2
#define CMD_WITH_DELIMETER(cmd) String::Concat(CMD_STRING::GetCommandString(cmd),DELIMITER_SYMBOL)
#define MAX_LENGTH_OF_LENGTH 8