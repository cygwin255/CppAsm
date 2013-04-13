#ifndef DIV_H
#define DIV_H

#include "AsmOperator.h"
#include "defs.h"
#include "Help.h"
#include "CodeArray.h"

class OpDiv : public AsmOperator
{
public:
	OpDiv();
	virtual void Do(const byte &, Code &, const RegisterWord &reg);
	virtual void ProcessParsedLine(const RegisterWord &, const RegisterWord &, CodeArray &, bool);
};

OpDiv::OpDiv()
{
}

void OpDiv::Do(const byte &b, Code &code, const RegisterWord &reg)
{
	RegisterWord r;
	Help::getWordFromStack(code, r);

	code.getRegister(reg.getRightRegister()) /= r;
}

void OpDiv::ProcessParsedLine(const RegisterWord &regLeft, const RegisterWord &regRight, CodeArray &codeArray, bool isAltPush)
{
	codeArray.Add(isAltPush ? Help::PUSH_ALT : Help::PUSH, regRight);
	codeArray.Add(Help::DIV, regLeft);
}


#endif