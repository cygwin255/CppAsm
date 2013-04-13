#ifndef MOV_H
#define MOV_H

#include "AsmOperator.h"
#include "defs.h"

#include "CodeArray.h"

class OpMov : public AsmOperator
{
public:
	OpMov();
	virtual void Do(const byte &, Code &, const RegisterWord &reg);
	virtual void ProcessParsedLine(const RegisterWord &, const RegisterWord &, CodeArray &, bool);
};

OpMov::OpMov()
{
}

void OpMov::Do(const byte &b, Code &code, const RegisterWord &reg)
{
	RegisterWord r;
	Help::getWordFromStack(code, r);

	code.getRegister(reg.getRightRegister()) = r;
}

void OpMov::ProcessParsedLine(const RegisterWord &regLeft, const RegisterWord &regRight, CodeArray &codeArray, bool isAltPush)
{
	codeArray.Add(isAltPush ? Help::PUSH_ALT : Help::PUSH, regRight);
	codeArray.Add(Help::MOV, regLeft);
}


#endif