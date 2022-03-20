#include "dev_tools.h"

void Debugger::Log(std::string message, std::string * debug_folder_name)
{
	time_t rawtime;
	struct tm timePtr;
	time(&rawtime);
	localtime_s(&timePtr, &rawtime);

	std::ofstream log(*debug_folder_name+"\\Log.txt", std::ios::app);

	log << std::to_string(timePtr.tm_hour) <<':'<< std::to_string(timePtr.tm_min) << ':' << std::to_string(timePtr.tm_sec) << " | " << message << std::endl;

	log.close();
}

void create_debug_folder(std::string * debug_folder_name)
{
	time_t rawtime;
	struct tm timePtr;
	time(&rawtime);
	localtime_s(&timePtr, &rawtime);
	*debug_folder_name = ".\\Debug\\logs\\" + std::to_string(timePtr.tm_mday) + '.' + std::to_string(1 + timePtr.tm_mon) + '.' + std::to_string(1900 + timePtr.tm_year);
	system(("mkdir " + *debug_folder_name).c_str());
}