#ifndef INT_H
#define INT_H

#include <iostream>


#include "AsmOperator.h"
#include "defs.h"
#include "CodeArray.h"
#include "Interrupt.h"

class OpInt : public AsmOperator
{
public:
	OpInt();
	virtual void Do(const byte &, Code &, const RegisterWord &reg);
	virtual void ProcessParsedLine(const RegisterWord &, const RegisterWord &, CodeArray &, bool);
};

OpInt::OpInt()
{
}

void OpInt::Do(const byte &b, Code &code, const RegisterWord &r)
{
	cout << uppercase;

	Interrupt::getInstance()->performInterrupt(r.getRightRegister(), code);
}

void OpInt::ProcessParsedLine(const RegisterWord &regLeft, const RegisterWord &regRight, CodeArray &codeArray, bool isAltPush)
{
	codeArray.Add(Help::INT, regLeft);
}


#endif