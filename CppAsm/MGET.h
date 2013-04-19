#ifndef MGET_H
#define MGET_H

#include "AsmOperator.h"
#include "defs.h"
#include "CodeArray.h"

class OpMget : public AsmOperator
{
public:
	OpMget();
	virtual void Do(const byte &, Code &, const RegisterWord &reg);
	virtual void ProcessParsedLine(const RegisterWord &, const RegisterWord &, CodeArray &, bool);
};

OpMget::OpMget()
{
}

void OpMget::Do(const byte &b, Code &code, const RegisterWord &reg)
{
	RegisterWord offset;
	Help::getWordFromStack(code, offset);

	int ds = code.getRegister(Help::DS).getValue() + offset.getValue();
	
	RegisterWord *refer = &code.getRegister(reg.getRightRegister());

	if (refer->leftright == -1)
		refer->setLeftRegister(*code.memory[ds]);
	else if (refer->leftright == 1)
		refer->setRightRegister(*code.memory[ds]);
	else
	{
		refer->setRightRegister(*code.memory[ds + 1]);
		refer->setLeftRegister(*code.memory[ds]);
	}
}

void OpMget::ProcessParsedLine(const RegisterWord &regLeft, const RegisterWord &regRight, CodeArray &codeArray, bool isAltPush)
{
	codeArray.Add(isAltPush ? Help::PUSH_ALT : Help::PUSH, regRight);
	codeArray.Add(Help::MGET, regLeft);
}


#endif