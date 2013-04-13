#ifndef INC_H
#define INC_H

#include "AsmOperator.h"
#include "defs.h"

#include "CodeArray.h"

class OpInc : public AsmOperator
{
public:
	OpInc();
	virtual void Do(const byte &, Code &, const RegisterWord &reg);
	virtual void ProcessParsedLine(const RegisterWord &, const RegisterWord &, CodeArray &, bool);
};

OpInc::OpInc()
{
}

void OpInc::Do(const byte &b, Code &code, const RegisterWord &reg)
{
	code.getRegister(reg.getRightRegister()) += 1;
}

void OpInc::ProcessParsedLine(const RegisterWord &regLeft, const RegisterWord &regRight, CodeArray &codeArray, bool isAltPush)
{
	codeArray.Add(Help::INC, regLeft);
}


#endif