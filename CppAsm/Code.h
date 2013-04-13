#ifndef CODE_H
#define CODE_H


#include "RegisterWord.h"
#include "defs.h"
#include "Stack.h"
#include "CodeArray.h"
//#include "AsmOperator.h"
#include "Memory.h"
#include "Debug.h"

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
private:
	Debug deb;
	bool zeroFlag;
	bool greaterFlag;

	bool debug;
	RegisterWord registers[20];
};


#endif