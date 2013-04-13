#ifndef CMP_H
#define CMP_H

#include "AsmOperator.h"
#include "defs.h"

#include "CodeArray.h"

class OpCmp : public AsmOperator
{
public:
	OpCmp();
	virtual void Do(const byte &, Code &, const RegisterWord &reg);
	virtual void ProcessParsedLine(const RegisterWord &, const RegisterWord &, CodeArray &, bool);
};

OpCmp::OpCmp()
{
}

void OpCmp::Do(const byte &b, Code &code, const RegisterWord &reg)
{
	RegisterWord r;
	Help::getWordFromStack(code, r);

	RegisterWord r2 = code.getRegister(reg.getRightRegister());

	int i1 = r2.getLeftRegister();
	int i2 = r2.getRightRegister();

	RegisterWord out;

	if (r.getValue() != r2.getValue())
		code.setZeroFlag(true);
	else 
		code.setZeroFlag(false);

	if (r.getValue() < r2.getValue())
		code.setGreaterFlag(true);
	else 
		code.setGreaterFlag(false);

}

void OpCmp::ProcessParsedLine(const RegisterWord &regLeft, const RegisterWord &regRight, CodeArray &codeArray, bool isAltPush)
{
	codeArray.Add(isAltPush ? Help::PUSH_ALT : Help::PUSH, regRight);
	codeArray.Add(Help::CMP, regLeft);
}


#endif