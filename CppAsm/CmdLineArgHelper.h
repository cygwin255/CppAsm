#ifndef CMD_HELP_H
#define CMD_HELP_H

class CmdLineArgHelper
{
public:
	static bool findFlag(int, char **, const char *);
	static const char *findFlagParameter(int, char **, const char *);
	static bool isFileExists(const char *);
};

#endif