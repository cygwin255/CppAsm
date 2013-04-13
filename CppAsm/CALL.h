#ifndef CALL_H
#define CALL_H

#include "AsmOperator.h"
#include "defs.h"

#include "CodeArray.h"

class OpCall : public AsmOperator
{
public:
	OpCall();
	virtual void Do(const byte &, Code &, const RegisterWord &reg);
	virtual void ProcessParsedLine(const RegisterWord &, const RegisterWord &, CodeArray &, bool);
};

OpCall::OpCall()
{
}

void OpCall::Do(const byte &b, Code &code, const RegisterWord &reg)
{
	RegisterWord r;
	r.setValue(code.getRegister(Help::IP).getValue());
	Help::putWordToStack(code, r);

	code.getRegister(Help::IP) = reg;
	//code.getRegister(Help::IP) *= 3;
}

void OpCall::ProcessParsedLine(const RegisterWord &regLeft, const RegisterWord &regRight, CodeArray &codeArray, bool isAltPush)
{
	codeArray.Add(Help::CALL, regLeft);
}


#endif