#ifndef ADD_H
#define ADD_H

#include "AsmOperator.h"
#include "defs.h"
#include "Help.h"
//#include "CodeArray.h"



class OpAdd : public AsmOperator
{
public:
	OpAdd();
	virtual void Do(const byte &, Code &, const RegisterWord &reg);
	virtual void ProcessParsedLine(const RegisterWord &, const RegisterWord &, CodeArray &, bool);
};

OpAdd::OpAdd()
{
}

void OpAdd::Do(const byte &b, Code &code, const RegisterWord &reg)
{
	RegisterWord r;
	Help::getWordFromStack(code, r);

	code.getRegister(reg.getRightRegister()) += r;
}

void OpAdd::ProcessParsedLine(const RegisterWord &regLeft, const RegisterWord &regRight, CodeArray &codeArray, bool isAltPush)
{
	codeArray.Add(isAltPush ? Help::PUSH_ALT : Help::PUSH, regRight);
	codeArray.Add(Help::ADD, regLeft);
}


#endif