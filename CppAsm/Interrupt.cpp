#include "Interrupt.h"

#include <exception>
#include <iostream>

#include "Code.h"
#include "Help.h"

using namespace std;

Interrupt *Interrupt::_instance = 0;

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
	if (m_Functions[id] == 0)
		throw runtime_error("id not found in Interrupt::performInterrupt");
		
	(this->*m_Functions[id])(code);
}
/* === :: ������� BP :: ===
 * 00 - ����� � 10 c/c
 * 01 - ����� � 16 c/c
 * 
 * === :: ������� :: ===
 * 00h
 *    ��������� ���� ��� ������
 * 01h 
 *	  ��������� ����� ��� ��� �������
 * 02h 
 *    ��������� ���� ��� �����
 * 03h
 *    ��������� ����� ��� �����
 * 04h
 *    ������� ���� ��� ������
 * 05h
 *    ������� ����� ��� ��� �������
 * 06h
 *    ������� ���� ��� �����
 * 07h
 *    ������� ����� ��� �����
 * 08h
 *    ����� �� ��������� 
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

	cout << reg.getRightRegister();
}
void Interrupt::Int05h(Code &code)
{
	RegisterWord reg;
	Help::getWordFromStack(code, reg);

	cout << reg.getLeftRegister() << reg.getRightRegister();
}
void Interrupt::Int06h(Code &code)
{
	RegisterWord reg;
	Help::getWordFromStack(code, reg);

	if (code.getRegister(Help::BP).getRightRegister() == 0x01)
		cout << hex;

	cout << (int)reg.getRightRegister();
}
void Interrupt::Int07h(Code &code)
{
	RegisterWord reg;
	Help::getWordFromStack(code, reg);

	if (code.getRegister(Help::BP).getRightRegister() == 0x01)
		cout << hex;

	cout << reg.getValue();
}
void Interrupt::Int08h(Code &code)
{
	code.setExitProgram(true);
}
