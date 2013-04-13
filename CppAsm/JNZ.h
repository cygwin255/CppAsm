#ifndef JNZ_H
#define JNZ_H

#include "AsmOperator.h"
#include "defs.h"

#include "CodeArray.h"

class OpJnz : public AsmOperator
{
public:
	OpJnz();
	virtual void Do(const byte &, Code &, const RegisterWord &reg);
	virtual void ProcessParsedLine(const RegisterWord &, const RegisterWord &, CodeArray &, bool);
};

OpJnz::OpJnz()
{
}

void OpJnz::Do(const byte &b, Code &code, const RegisterWord &reg)
{
	if (code.isZeroFlag())
	{
		code.getRegister(Help::IP) = reg;
		//code.getRegister(Help::IP) *= 3;
	}
}

void OpJnz::ProcessParsedLine(const RegisterWord &regLeft, const RegisterWord &regRight, CodeArray &codeArray, bool isAltPush)
{
	codeArray.Add(Help::JNZ, regLeft);
}


#endif