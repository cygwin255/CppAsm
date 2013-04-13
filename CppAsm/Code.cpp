#include "Code.h"
#include "RegisterWord.h"
#include "defs.h"
#include "Help.h"
#include "AsmOperator.h"
#include "Debug.h"
#include <exception>
#include <iostream>
#include <fstream>

using namespace std;

Code::Code(const char * path)
{
	ifstream Input;
	Input.open(path, ios::binary);
	//TODO: �������� �������� �� �������� �������� �����
	if (!Input)
		throw runtime_error("Invalid path");
	//��������� ������ �����
	Input.seekg (0, Input.end);
	int length = Input.tellg();
	Input.seekg (0, Input.beg);

	//������ ����� ��� ���������� ����� �������
	char * buffer = new char [length];
	//���������
	Input.read(buffer, length);
	//���������� ����������
	codeArray.Add(buffer, length);
	//����������� ������
	delete [] buffer;

	Input.close();

	//��������� ���������
	getRegister(Help::CS).setValue(0); // �������� ������� ����
	getRegister(Help::DS).setLeftRegister(*codeArray[0]); // �������� ������� ������ - ������ ����
	getRegister(Help::DS).setRightRegister(*codeArray[1]); // �������� ������� ������ - ������ ����

	//������ ��������� � ����������� ������
	int i;
	for(i=2;i<codeArray.getSize();i++)
		*memory[i-2] = *codeArray[i];

	getRegister(Help::DS) -= 2;

	//��������� ���������
	getRegister(Help::SS).setValue(i); // �������� ������� �����
	getRegister(Help::IP).setValue(0); // �������(�������) ������
	getRegister(Help::SP).setValue(0); // ��������� �� ������� �����

	deb.setCode(this);
	setZeroFlag(false);
	setGreaterFlag(false);
	exit = false;
}

void Code::Run()
{
	//����(�.� ���������) ����������� �� ��� ���, ���� ������� ������ �� ��������� ������� DS, �.� ������
	while( !isExitProgram() )
	{
		//���������� �����
		int addr = getRegister(Help::CS).getValue() + getRegister(Help::IP).getValue();

		if (isDebug())
			deb.Update(addr);
		
		//������� ������� ������� ������ �� 3(�.� ������ ������� = 3 �����)
		getRegister(Help::IP) += 3;
		//�������� ��� �������
		byte operation = *memory[addr++];

		//��������� 2 ����� - �����, ��� ������ ���������� � �������
		RegisterWord reg;
		reg.setLeftRegister(*memory[addr++]);
		reg.setRightRegister(*memory[addr++]);

		//�������� ��������������� ��������
		AsmOperator *curOperator = AsmOperator::newOperator(operation);
		//��������� ��������
		curOperator->Do(operation, *this, reg);
		//����������� ������
		delete curOperator;
	}
}


RegisterWord &Code::getRegister(byte index)
{
	switch (index)
	{
	case 0x01:
		registers[0].leftright = -1;
		return registers[0]; 
	case 0x02:
		registers[0].leftright = 1;
		return registers[0]; 
	case 0x04:
		registers[3].leftright = -1;
		return registers[3];
	case 0x05:
		registers[3].leftright = 1;
		return registers[3];
	case 0x07:
		registers[6].leftright = -1;
		return registers[6];
	case 0x08:
		registers[6].leftright = 1;
		return registers[6];
	case 0x0A:
		registers[9].leftright = -1;
		return registers[9];
	case 0x0B:
		registers[9].leftright = 1;
		return registers[9];
	}

	registers[index].leftright = 0;
	return registers[index];
}
