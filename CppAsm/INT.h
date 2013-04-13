#ifndef INT_H
#define INT_H

#include "AsmOperator.h"
#include "defs.h"
#include <iostream>
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


/* if (r.getValue() == 0x0000)
	{
		char buf[1];
		cin.read(buf, 1);
		out.setValue(buf[0]);
		Help::putWordToStack(code, out);
	}
	else if (r.getValue() == 0x0001)
	{
		char buf[2];
		cin.read(buf, 2);
		out.setRightRegister(buf[0]);
		out.setLeftRegister(buf[1]);
		Help::putWordToStack(code, out);
	}
	else if (r.getValue() == 0x0002)
	{
		short buf;
		cin >> buf;
		out.setValue(buf % 0x100);
		Help::putWordToStack(code, out);
	}
	else if (r.getValue() == 0x0003)
	{
		short buf;
		cin >> buf;
		out.setValue(buf);
		Help::putWordToStack(code, out);
	}
	else if (r.getValue() == 0x0004)
	{
		RegisterWord rg;
		Help::getWordFromStack(code, rg);

		cout << hex << rg.getRightRegister();
	}
	else if (r.getValue() == 0x0005)
	{
		RegisterWord rg;
		Help::getWordFromStack(code, rg);

		cout << rg.getValue();
	}
	else if (r.getValue() == 0x0006)
	{
		RegisterWord rg;
		Help::getWordFromStack(code, rg);

		if (rg.getLeftRegister() != 0)
			cout << rg.getLeftRegister();
		else if (rg.getRightRegister() != 0)
			cout << rg.getRightRegister();
	}
	else if (r.getValue() == 0x0007)
	{
		RegisterWord rg;
		Help::getWordFromStack(code, rg);

		cout <<rg.getLeftRegister() << rg.getRightRegister();
	}*/
}

void OpInt::ProcessParsedLine(const RegisterWord &regLeft, const RegisterWord &regRight, CodeArray &codeArray, bool isAltPush)
{
	codeArray.Add(Help::INT, regLeft);
}


#endif