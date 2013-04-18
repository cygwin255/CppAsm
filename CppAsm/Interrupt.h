#ifndef INTERRUPT_H
#define INTERRUPT_H

#include <map>

#include "defs.h"
#include "Code.h"


class Interrupt
{
public:
	static Interrupt *getInstance();

	void performInterrupt(const byte &, Code &);

protected:
	Interrupt();


private:	
	static Interrupt *_instance;

	std::map<byte, void (Interrupt::*)(Code &)> m_Functions;

	void Int00h(Code &);
	void Int01h(Code &);
	void Int02h(Code &);
	void Int03h(Code &);
	void Int04h(Code &);
	void Int05h(Code &);
	void Int06h(Code &);
	void Int07h(Code &);
	void Int08h(Code &);

};

#endif