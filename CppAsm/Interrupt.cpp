#include "Interrupt.h"

#include <exception>
#include <iostream>

#include "Code.h"
#include "Help.h"

using namespace std;

Interrupt *Interrupt::_instance = 0;

Interrupt * Interrupt::getInstance()
{
	if (_instance == 0)
		_instance = new Interrupt();

	return _instance;
}


Interrupt::Interrupt()
{
	m_Functions[0] = &Interrupt::Int00h;
	m_Functions[1] = &Interrupt::Int01h;
	m_Functions[2] = &Interrupt::Int02h;
	m_Functions[3] = &Interrupt::Int03h;
	m_Functions[4] = &Interrupt::Int04h;
	m_Functions[5] = &Interrupt::Int05h;
	m_Functions[6] = &Interrupt::Int06h;
	m_Functions[7] = &Interrupt::Int07h;
	m_Functions[8] = &Interrupt::Int08h;

}


void Interrupt::performInterrupt(const byte &id, Code &code)
{		
	(this->*m_Functions[id])(code);
}
/* === :: Регистр BP :: ===
 * 00 - вывод в 10 c/c
 * 01 - вывод в 16 c/c
 * 
 * === :: Команды :: ===
 * 00h
 *    Прочитать байт как символ
 * 01h 
 *	  Прочитать слово как два символа
 * 02h 
 *    Прочитать байт как число
 * 03h
 *    Прочитать слово как число
 * 04h
 *    Вывести байт как символ
 * 05h
 *    Вывести слово как два символа
 * 06h
 *    Вывести байт как число
 * 07h
 *    Вывести слово как число
 * 08h
 *    Выход из программы 
 */
void Interrupt::Int00h(Code &code)
{
	RegisterWord out;
	char buf[1];
	cin.read(buf, 1);
	out.setValue(buf[0]);
	Help::putWordToStack(code, out);
}
void Interrupt::Int01h(Code &code)
{
	RegisterWord out;
	char buf[2];
	cin.read(buf, 2);
	out.setLeftRegister(buf[0]);
	out.setRightRegister(buf[1]);
	Help::putWordToStack(code, out);
}
void Interrupt::Int02h(Code &code)
{
	RegisterWord out;
	byte i;
	cin >> i;
	out.setValue(i);
	Help::putWordToStack(code, out);
}
void Interrupt::Int03h(Code &code)
{
	RegisterWord out;
	word i;
	cin >> i;
	out.setValue(i);
	Help::putWordToStack(code, out);
}
void Interrupt::Int04h(Code &code)
{
	RegisterWord reg;
	Help::getWordFromStack(code, reg);

	if (!code.isTrapFlag())
		cout << reg.getRightRegister();
}
void Interrupt::Int05h(Code &code)
{
	RegisterWord reg;
	Help::getWordFromStack(code, reg);
	
	if (!code.isTrapFlag())
		cout << reg.getLeftRegister() << reg.getRightRegister();
}
void Interrupt::Int06h(Code &code)
{
	RegisterWord reg;
	Help::getWordFromStack(code, reg);

	if (!code.isTrapFlag())
	{
		if (code.getRegister(Help::BP).getRightRegister() == 0x01)
			cout << hex;
	
		cout << (int)reg.getRightRegister();
	}
}
void Interrupt::Int07h(Code &code)
{
	RegisterWord reg;
	Help::getWordFromStack(code, reg);
	if (!code.isTrapFlag())
	{
		if (code.getRegister(Help::BP).getRightRegister() == 0x01)
			cout << hex;

		cout << reg.getValue();
	}
}
void Interrupt::Int08h(Code &code)
{
	code.setExitProgram(true);
}