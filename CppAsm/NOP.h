#ifndef NOP_H
#define NOP_H

#include "AsmOperator.h"
#include "defs.h"

#include "CodeArray.h"

class OpNop : public AsmOperator
{
public:
	OpNop();
	virtual void Do(const byte &, Code &, const RegisterWord &reg);
	virtual void ProcessParsedLine(const RegisterWord &, const RegisterWord &, CodeArray &, bool);
};

OpNop::OpNop()
{
}

void OpNop::Do(const byte &b, Code &code, const RegisterWord &reg)
{
	//не знаю зачем я сделал nop... ну да ладно ;)
}

void OpNop::ProcessParsedLine(const RegisterWord &regLeft, const RegisterWord &regRight, CodeArray &codeArray, bool isAltPush)
{
	codeArray.Add(Help::NOP, 0x0000);
}


#endif