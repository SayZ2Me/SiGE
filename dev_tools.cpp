#include "dev_tools.h"

void Debugger::log(std::string message)
{
	time_t rawtime;
	struct tm timePtr;
	time(&rawtime);
	localtime_s(&timePtr, &rawtime);

	std::ofstream log(debug_folder_name+"\\Log.txt", std::ios::app);

	log << std::to_string(timePtr.tm_hour) <<':'<< std::to_string(timePtr.tm_min) << ':' << std::to_string(timePtr.tm_sec) << " | " << message << std::endl;

	log.close();
}
void Debugger::setDebugFolderName(std::string debug_folder_name)
{
	this->debug_folder_name = debug_folder_name;
}
void create_debug_folder(Debugger* Debug)
{
	time_t rawtime;
	struct tm timePtr;
	time(&rawtime);
	localtime_s(&timePtr, &rawtime);
	std::string debug_folder_name = ".\\Debug\\logs\\" + std::to_string(timePtr.tm_mday) + '.' + std::to_string(1 + timePtr.tm_mon) + '.' + std::to_string(1900 + timePtr.tm_year);
	Debug->setDebugFolderName(debug_folder_name);
	system(("mkdir " + debug_folder_name).c_str());
}