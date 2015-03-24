#ifndef ROL_H
#define ROL_H

#include "AsmOperator.h"
#include "defs.h"
#include "Help.h"
//#include "CodeArray.h"



class OpRol : public AsmOperator
{
public:
	OpRol();
	virtual void Do(const byte &, Code &, const RegisterWord &reg);
	virtual void ProcessParsedLine(const RegisterWord &, const RegisterWord &, CodeArray &, bool);
};

OpRol::OpRol()
{
}

void OpRol::Do(const byte &b, Code &code, const RegisterWord &reg)
{
	RegisterWord r;
	Help::getWordFromStack(code, r);

	word rg = code.getRegister(reg.getRightRegister()).getValue();
	word rr = r.getValue() % 16;

	code.getRegister(reg.getRightRegister()).setValue((rg << rr) + (rg >> (16 - rr)));
}

void OpRol::ProcessParsedLine(const RegisterWord &regLeft, const RegisterWord &regRight, CodeArray &codeArray, bool isAltPush)
{
	codeArray.Add(isAltPush ? Help::PUSH_ALT : Help::PUSH, regRight);
	codeArray.Add(Help::ROL, regLeft);
}


#endif