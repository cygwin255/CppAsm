#ifndef COMPILER_H
#define COMPILER_H

#include "defs.h"
#include "RegisterWord.h"

#include <regex>
#include <map>
#include <cstring>
#include "CodeArray.h"
#include <sstream>
#include <list>
using namespace std;

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

	void readFile(const char *, istringstream &);
	
	void parseUses(const string &, CodeArray &, list<RegisterWord> &);

	void parseAllLabels(const char *, map<longint, int> &);
	void parseRegisters(const smatch &, RegisterWord &, int, bool &, bool &);
	void parseAllData(const char *, map<longint, int> &, string &);

	void parseNullDataArray(string &, smatch &, int &);
	void parseDataString(string &, smatch &, int &);
	void parseFullDataArray(string &, smatch &, int &);


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

	static const regex COMMAND_PARSE_REGEX;
	static const regex LABEL_PARSE_REGEX;
	static const regex DATA_PARSE_REGEX;
	static const regex DATA_ARRAY_PARSE_REGEX;
	static const regex REMOVE_COMMENTS_REGEX;
	static const regex USES_PARSE_REGEX;
	static const regex OPERATORS_LIST_PARSE_REGEX;
};

#endif