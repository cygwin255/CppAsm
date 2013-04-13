#ifndef MSET_H
#define MSET_H

#include "AsmOperator.h"
#include "defs.h"

#include "CodeArray.h"

class OpMset : public AsmOperator
{
public:
	OpMset();
	virtual void Do(const byte &, Code &, const RegisterWord &reg);
	virtual void ProcessParsedLine(const RegisterWord &, const RegisterWord &, CodeArray &, bool);
};

OpMset::OpMset()
{
}

void OpMset::Do(const byte &b, Code &code, const RegisterWord &reg)
{
	//получаем дополнительный аргумент
	RegisterWord offset;
	Help::getWordFromStack(code, offset);

	int ds = code.getRegister(Help::DS).getValue() + offset.getValue();

	RegisterWord *refer = &code.getRegister(reg.getRightRegister());

	if (refer->leftright == -1)
		(*code.memory[ds]) = refer->getLeftRegister();
	else if (refer->leftright == 1)
		(*code.memory[ds]) = refer->getRightRegister();
	else
	{
		(*code.memory[ds]) = refer->getLeftRegister();
		(*code.memory[ds + 1]) = refer->getRightRegister();
	}
}

void OpMset::ProcessParsedLine(const RegisterWord &regLeft, const RegisterWord &regRight, CodeArray &codeArray, bool isAltPush)
{
	codeArray.Add(isAltPush ? Help::PUSH_ALT : Help::PUSH, regRight);
	codeArray.Add(Help::MSET, regLeft);
}


#endif