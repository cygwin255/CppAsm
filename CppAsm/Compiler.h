#ifndef COMPILER_H
#define COMPILER_H

#include <regex>
#include <map>
#include <cstring>
#include <sstream>
#include <list>


#include "defs.h"
#include "RegisterWord.h"
#include "CodeArray.h"


class Compiler
{
public:
	static Compiler *getInstance();
	
	int Compile(const char *, const char *);
protected:
	Compiler();
private:
	static Compiler *_instance;

	
	
	//internal use only:

	void readFile(const char *, std::istringstream &);
	
	bool parseUses(const std::string &, CodeArray &, std::list<RegisterWord> &);

	void parseAllLabels(std::istringstream &, std::map<longint, int> &, std::map<int, std::map<longint, int> > &);
	void parseRegisters(const std::smatch &, RegisterWord &, int, bool &, bool &);
	void parseAllData(std::istringstream &, std::map<longint, int> &, std::string &);

	void parseNullDataArray(std::string &, std::smatch &, int &);
	void parseDataString(std::string &, std::smatch &, int &);
	void parseFullDataArray(std::string &, std::smatch &, int &);


	//static const:
	static const int COMMAND_REGEX_INDEX;
	static const int LEFT_OPERAND_REGEX_INDEX;
	static const int RIGHT_OPERAND_REGEX_INDEX;
	static const int LABEL_COMMAND_REGEX_INDEX;
	static const int DATA_LABEL_REGEX_INDEX;
	static const int DATA_TYPE_REGEX_INDEX;
	static const int DATA_ARRAY_REGEX_INDEX;
	static const int DATA_TEXT_REGEX_INDEX;
	static const int DATA_DATA_REGEX_INDEX;
	static const int USES_REGEX_INDEX;

	static const int BUFFER_SIZE;

	static const std::regex COMMAND_PARSE_REGEX;
	static const std::regex LABEL_PARSE_REGEX;
	static const std::regex DATA_PARSE_REGEX;
	static const std::regex DATA_ARRAY_PARSE_REGEX;
	static const std::regex REMOVE_COMMENTS_REGEX;
	static const std::regex USES_PARSE_REGEX;
	static const std::regex OPERATORS_LIST_PARSE_REGEX;
};

#endif