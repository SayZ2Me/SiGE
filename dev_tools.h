#include <fstream>
#include <string>

#pragma once

class Debugger
{
public:
	void Log(std::string message, std::string * debug_folder_name);
};

void create_debug_folder(std::string *  debug_folder_name);