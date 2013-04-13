#ifndef MOD_H
#define MOD_H

#include "AsmOperator.h"
#include "defs.h"
#include "Help.h"

class OpMod : public AsmOperator
{
public:
	OpMod();
	virtual void Do(const byte &, Code &, const RegisterWord &reg);
	virtual void ProcessParsedLine(const RegisterWord &, const RegisterWord &, CodeArray &, bool);
};

OpMod::OpMod()
{
}

void OpMod::Do(const byte &b, Code &code, const RegisterWord &reg)
{
	RegisterWord r;
	Help::getWordFromStack(code, r);

	code.getRegister(reg.getRightRegister()) %= r;
}

void OpMod::ProcessParsedLine(const RegisterWord &regLeft, const RegisterWord &regRight, CodeArray &codeArray, bool isAltPush)
{
	codeArray.Add(isAltPush ? Help::PUSH_ALT : Help::PUSH, regRight);
	codeArray.Add(Help::MOD, regLeft);
}


#endif