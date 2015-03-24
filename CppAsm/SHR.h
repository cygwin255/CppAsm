#ifndef SHR_H
#define SHR_H

#include "AsmOperator.h"
#include "defs.h"
#include "Help.h"
//#include "CodeArray.h"



class OpShr : public AsmOperator
{
public:
	OpShr();
	virtual void Do(const byte &, Code &, const RegisterWord &reg);
	virtual void ProcessParsedLine(const RegisterWord &, const RegisterWord &, CodeArray &, bool);
};

OpShr::OpShr()
{
}

void OpShr::Do(const byte &b, Code &code, const RegisterWord &reg)
{
	RegisterWord r;
	Help::getWordFromStack(code, r);

	code.getRegister(reg.getRightRegister()).setValue(code.getRegister(reg.getRightRegister()).getValue() >> (r.getValue() % 16));
}

void OpShr::ProcessParsedLine(const RegisterWord &regLeft, const RegisterWord &regRight, CodeArray &codeArray, bool isAltPush)
{
	codeArray.Add(isAltPush ? Help::PUSH_ALT : Help::PUSH, regRight);
	codeArray.Add(Help::SHR, regLeft);
}


#endif