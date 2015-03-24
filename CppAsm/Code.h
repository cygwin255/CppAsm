#ifndef CODE_H
#define CODE_H


#include "RegisterWord.h"
#include "defs.h"
#include "CodeArray.h"
#include "Memory.h"
#include "Debug.h"

class AsmOperator;

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
	
	bool isDebug() const { return debugFlag; }
	void setDebug(bool val) { debugFlag = val; }

	bool isGreaterFlag() const { return greaterFlag; }
	void setGreaterFlag(bool val) { greaterFlag = val; }

	bool isTrapFlag() const { return isDebug(); }
	void setTrapFlag(bool val) { setDebug(val); }

	void setExitProgram(bool val) { exit = val; }
	bool isExitProgram() const { return exit; }
private:
	Debug deb;
	bool zeroFlag;
	bool greaterFlag;
	bool debugFlag;
	bool exit;

	RegisterWord registers[21];
};


#endif