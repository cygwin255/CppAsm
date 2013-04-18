#include <cstring>
#include <fstream>


#include "CmdLineArgHelper.h"

using namespace std;

bool CmdLineArgHelper::findFlag(int argc, char **argv, const char *param)
{
	for(int i=0;i<argc;i++)
		if (!strcmp(param, argv[i]))
			return true;

	return false;
}

const char *CmdLineArgHelper::findFlagParameter(int argc, char **argv, const char *param)
{
	for(int i=0;i<argc;i++)
		if (!strcmp(param, argv[i]))
			return argv[i + 1];

	return "";
}

bool CmdLineArgHelper::isFileExists(const char *filePath)
{
	ifstream file(filePath);
	
	bool b = !file;
	
	file.close();
	return !b;
}
