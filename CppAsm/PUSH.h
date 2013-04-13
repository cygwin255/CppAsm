#ifndef PUSH_H
#define PUSH_H

#include "AsmOperator.h"
#include "defs.h"

#include "CodeArray.h"
#include "Help.h"

class OpPush : public AsmOperator
{
public:
	OpPush();
	virtual void Do(const byte &, Code &, const RegisterWord &reg);
	virtual void ProcessParsedLine(const RegisterWord &, const RegisterWord &, CodeArray &, bool);
};

OpPush::OpPush()
{
}

void OpPush::Do(const byte &b, Code &code, const RegisterWord &reg)
{
	if (b == Help::PUSH_ALT)
	{
		Help::putWordToStack(code, reg);
	}
	else
	{

		RegisterWord r = code.getRegister(reg.getRightRegister());

		int ip = code.getRegister(Help::SS).getValue() + code.getRegister(Help::SP).getValue();

		if (r.leftright == -1)
		{
			*code.memory[ip] = 0;
			*code.memory[ip + 1] = r.getLeftRegister();
		}
		else if (r.leftright == 1)
		{
			*code.memory[ip] = 0;
			*code.memory[ip + 1] = r.getRightRegister();
		}
		else
		{
			*code.memory[ip] = r.getLeftRegister();
			*code.memory[ip + 1] = r.getRightRegister();
		}
// 		*code.memory[] = r.getLeftRegister();
// 		code.getRegister(Help::SP) += 1;
// 		*code.memory[code.getRegister(Help::SS).getValue() + code.getRegister(Help::SP).getValue()] = r.getRightRegister();
		code.getRegister(Help::SP) += 2;
		
	}

}

void OpPush::ProcessParsedLine(const RegisterWord &regLeft, const RegisterWord &regRight, CodeArray &codeArray, bool isAltPush)
{
	codeArray.Add(isAltPush ? Help::PUSH_ALT : Help::PUSH, regLeft);
}


#endif