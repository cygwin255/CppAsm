#ifndef JMP_H
#define JMP_H

#include "AsmOperator.h"
#include "defs.h"

#include "CodeArray.h"

class OpJmp : public AsmOperator
{
public:
	OpJmp();
	virtual void Do(const byte &, Code &, const RegisterWord &reg);
	virtual void ProcessParsedLine(const RegisterWord &, const RegisterWord &, CodeArray &, bool);
};

OpJmp::OpJmp()
{
}

void OpJmp::Do(const byte &b, Code &code, const RegisterWord &reg)
{
	code.getRegister(Help::IP) = reg;
	//code.getRegister(Help::IP) *= 3;
}

void OpJmp::ProcessParsedLine(const RegisterWord &regLeft, const RegisterWord &regRight, CodeArray &codeArray, bool isAltPush)
{
	codeArray.Add(Help::JMP, regLeft);
}


#endif