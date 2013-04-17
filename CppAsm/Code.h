#ifndef CODE_H
#define CODE_H


#include "RegisterWord.h"
#include "defs.h"
#include "CodeArray.h"
#include "Memory.h"
#include "Debug.h"


#include <iterator>

class AsmOperator;

using namespace std;

class Code
{
public:

	Code(const char *);

	void Run();

	RegisterWord &getRegister(byte);
	
	Memory memory;
	CodeArray codeArray;

	bool isZeroFlag() const { return zeroFlag; }
	void setZeroFlag(bool val) { zeroFlag = val; }
	
	bool isDebug() const { return debug; }
	void setDebug(bool val) { debug = val; }

	bool isGreaterFlag() const { return greaterFlag; }
	void setGreaterFlag(bool val) { greaterFlag = val; }

	void setExitProgram(bool val) { exit = val; }
	bool isExitProgram() const { return exit; }
private:
	Debug deb;
	bool zeroFlag;
	bool greaterFlag;
	bool exit;

	bool debug;
	RegisterWord registers[20];
};


#endif