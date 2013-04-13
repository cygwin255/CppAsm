#ifndef MUL_H
#define MUL_H

#include "AsmOperator.h"
#include "defs.h"

#include "CodeArray.h"

class OpMul : public AsmOperator
{
public:
	OpMul();
	virtual void Do(const byte &, Code &, const RegisterWord &reg);
	virtual void ProcessParsedLine(const RegisterWord &, const RegisterWord &, CodeArray &, bool);
};

OpMul::OpMul()
{
}

void OpMul::Do(const byte &b, Code &code, const RegisterWord &reg)
{
	RegisterWord r;
	Help::getWordFromStack(code, r);

	code.getRegister(reg.getRightRegister()) *= r;
}

void OpMul::ProcessParsedLine(const RegisterWord &regLeft, const RegisterWord &regRight, CodeArray &codeArray, bool isAltPush)
{
	codeArray.Add(isAltPush ? Help::PUSH_ALT : Help::PUSH, regRight);
	codeArray.Add(Help::MUL, regLeft);
}


#endif