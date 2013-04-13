#ifndef OPERATOR_H
#define OPERATOR_H

#include "defs.h"
#include "CodeArray.h"
#include "Code.h"
#include "Help.h"

class AsmOperator
{
public:
	AsmOperator();
	virtual void Do(const byte &, Code &, const RegisterWord &) = 0;
	virtual void ProcessParsedLine(const RegisterWord &, const RegisterWord &, CodeArray &, bool) = 0;
	static AsmOperator *newOperator(byte);

	//static const:
	static const char *Operators[];
	static const char *Registers[];
};

#endif