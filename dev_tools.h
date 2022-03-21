#include <fstream>
#include <string>

#pragma once

class Debugger
{
private:
	std::string debug_folder_name;
public:
	void log(std::string message);
	void setDebugFolderName(std::string debug_folder_name);
};

void create_debug_folder(Debugger * Debug);