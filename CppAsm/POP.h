#ifndef POP_H
#define POP_H

#include "AsmOperator.h"
#include "defs.h"

#include "CodeArray.h"

class OpPop : public AsmOperator
{
public:
	OpPop();
	virtual void Do(const byte &, Code &, const RegisterWord &reg);
	virtual void ProcessParsedLine(const RegisterWord &, const RegisterWord &, CodeArray &, bool);
};

OpPop::OpPop()
{
}

void OpPop::Do(const byte &b, Code &code, const RegisterWord &reg)
{
	RegisterWord rg;
	Help::getWordFromStack(code, rg);

	code.getRegister(reg.getRightRegister()) = rg;
}

void OpPop::ProcessParsedLine(const RegisterWord &regLeft, const RegisterWord &regRight, CodeArray &codeArray, bool isAltPush)
{
	codeArray.Add(Help::POP, regLeft);
}


#endif