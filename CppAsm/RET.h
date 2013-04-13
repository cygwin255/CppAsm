#ifndef RET_H
#define RET_H

#include "AsmOperator.h"
#include "defs.h"

#include "CodeArray.h"

class OpRet : public AsmOperator
{
public:
	OpRet();
	virtual void Do(const byte &, Code &, const RegisterWord &reg);
	virtual void ProcessParsedLine(const RegisterWord &, const RegisterWord &, CodeArray &, bool);
};

OpRet::OpRet()
{
}

void OpRet::Do(const byte &b, Code &code, const RegisterWord &reg)
{
	RegisterWord ip;
	Help::getWordFromStack(code, ip);
	
	code.getRegister(Help::IP) = ip;
}

void OpRet::ProcessParsedLine(const RegisterWord &regLeft, const RegisterWord &regRight, CodeArray &codeArray, bool isAltPush)
{
	codeArray.Add(Help::RET, 0x0000);
}


#endif