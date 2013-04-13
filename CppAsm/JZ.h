#ifndef JZ_H
#define JZ_H

#include "AsmOperator.h"
#include "defs.h"

#include "CodeArray.h"

class OpJz : public AsmOperator
{
public:
	OpJz();
	virtual void Do(const byte &, Code &, const RegisterWord &reg);
	virtual void ProcessParsedLine(const RegisterWord &, const RegisterWord &, CodeArray &, bool);
};

OpJz::OpJz()
{
}

void OpJz::Do(const byte &b, Code &code, const RegisterWord &reg)
{
	if (!code.isZeroFlag())
	{
		code.getRegister(Help::IP) = reg;
		//code.getRegister(Help::IP) *= 3;
	}
}

void OpJz::ProcessParsedLine(const RegisterWord &regLeft, const RegisterWord &regRight, CodeArray &codeArray, bool isAltPush)
{
	codeArray.Add(Help::JZ, regLeft);
}


#endif