#ifndef SUB_H
#define SUB_H

#include "AsmOperator.h"
#include "defs.h"
#include "Help.h"
#include "CodeArray.h"

class OpSub : public AsmOperator
{
public:
	OpSub();
	virtual void Do(const byte &, Code &, const RegisterWord &reg);
	virtual void ProcessParsedLine(const RegisterWord &, const RegisterWord &, CodeArray &, bool);
};

OpSub::OpSub()
{
}

void OpSub::Do(const byte &b, Code &code, const RegisterWord &reg)
{
	RegisterWord r;
	Help::getWordFromStack(code, r);
	
	code.getRegister(reg.getRightRegister()) -= r;
}

void OpSub::ProcessParsedLine(const RegisterWord &regLeft, const RegisterWord &regRight, CodeArray &codeArray, bool isAltPush)
{
	codeArray.Add(isAltPush ? Help::PUSH_ALT : Help::PUSH, regRight);
	codeArray.Add(Help::SUB, regLeft);
}


#endif