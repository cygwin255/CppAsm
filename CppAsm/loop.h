#ifndef LOOP_H
#define LOOP_H

#include "AsmOperator.h"
#include "defs.h"

#include "CodeArray.h"


class OpLoop : public AsmOperator
{
public:
	OpLoop();
	virtual void Do(const byte &, Code &, const RegisterWord &reg);
	virtual void ProcessParsedLine(const RegisterWord &, const RegisterWord &, CodeArray &, bool);
};

OpLoop::OpLoop()
{
}

void OpLoop::Do(const byte &b, Code &code, const RegisterWord &reg)
{
	if (code.getRegister(Help::CX).getValue() > 0)
	{
		code.getRegister(Help::IP) = reg;
		//code.getRegister(Help::IP) *= 3;

		code.getRegister(Help::CX) -= 1;
	}
}

void OpLoop::ProcessParsedLine(const RegisterWord &regLeft, const RegisterWord &regRight, CodeArray &codeArray, bool isAltPush)
{
	codeArray.Add(Help::LOOP, regLeft);
}


#endif