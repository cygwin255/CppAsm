#ifndef ROR_H
#define ROR_H

#include "AsmOperator.h"
#include "defs.h"
#include "Help.h"
//#include "CodeArray.h"



class OpRor : public AsmOperator
{
public:
	OpRor();
	virtual void Do(const byte &, Code &, const RegisterWord &reg);
	virtual void ProcessParsedLine(const RegisterWord &, const RegisterWord &, CodeArray &, bool);
};

OpRor::OpRor()
{
}

void OpRor::Do(const byte &b, Code &code, const RegisterWord &reg)
{
	RegisterWord r;
	Help::getWordFromStack(code, r);

	word rg = code.getRegister(reg.getRightRegister()).getValue();
	word rr = r.getValue() % 16;

	code.getRegister(reg.getRightRegister()).setValue((rg >> rr) + (rg << (16 - rr)));
}

void OpRor::ProcessParsedLine(const RegisterWord &regLeft, const RegisterWord &regRight, CodeArray &codeArray, bool isAltPush)
{
	codeArray.Add(isAltPush ? Help::PUSH_ALT : Help::PUSH, regRight);
	codeArray.Add(Help::ROR, regLeft);
}


#endif