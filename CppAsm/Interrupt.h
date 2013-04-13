#ifndef INTERRUPT_H
#define INTERRUPT_H

#include <map>

#include "defs.h"
#include "Code.h"

using namespace std;

class Interrupt
{
public:
	static Interrupt *getInstance()
	{
		if (_instance == 0)
			_instance = new Interrupt();

		return _instance;
	}

	void performInterrupt(const byte &, Code &);

protected:
	Interrupt();


private:	
	static Interrupt *_instance;

	map<byte, void (Interrupt::*)(Code &)> m_Functions;

	void Int00h(Code &);
	void Int01h(Code &);
	void Int02h(Code &);
	void Int03h(Code &);
	void Int04h(Code &);
	void Int05h(Code &);
	void Int06h(Code &);
	void Int07h(Code &);
	void Int08h(Code &);
/*
	void Int09h(Code &);
	void Int0Ah(Code &);
	void Int0Bh(Code &);
	void Int0Ch(Code &);
	void Int0Dh(Code &);
	void Int0Eh(Code &);
	void Int0Fh(Code &);
	void Int10h(Code &);
	void Int11h(Code &);*/



};

#endif