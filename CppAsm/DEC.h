#ifndef DEC_H
#define DEC_H

#include "AsmOperator.h"
#include "defs.h"

#include "CodeArray.h"

class OpDec : public AsmOperator
{
public:
	OpDec();
	virtual void Do(const byte &, Code &, const RegisterWord &reg);
	virtual void ProcessParsedLine(const RegisterWord &, const RegisterWord &, CodeArray &, bool);
};

OpDec::OpDec()
{
}

void OpDec::Do(const byte &b, Code &code, const RegisterWord &reg)
{
	code.getRegister(reg.getRightRegister()) -= 1;
}

void OpDec::ProcessParsedLine(const RegisterWord &regLeft, const RegisterWord &regRight, CodeArray &codeArray, bool isAltPush)
{
	codeArray.Add(Help::DEC, regLeft);
}


#endif