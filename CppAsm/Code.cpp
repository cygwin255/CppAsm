#include <iostream>
#include <fstream>
#include <algorithm>


#include "Code.h"
#include "RegisterWord.h"
#include "defs.h"
#include "Help.h"
#include "AsmOperator.h"
#include "Debug.h"

using namespace std;

Code::Code(const char * path)
{
	ifstream Input;
	Input.open(path, ios::binary);

	//вычисляем размер файла
	Input.seekg (0, Input.end);
	int length = Input.tellg();
	Input.seekg (0, Input.beg);

	//создаём буфер для считывания файла целиком
	char *buffer = new char [length];
	//считываем
	Input.read(buffer, length);
	//записываем информацию
	codeArray.Add(buffer, length);
	//освобождаем память
	delete [] buffer;

	Input.close();

	//установка регистров
	getRegister(Help::CS).setValue(0x0000); // сегмент кода
	getRegister(Help::DS).setValue(0x1000); // сегмент данных

	int ptr = ((byte)*codeArray[0] << 8) + (byte)*codeArray[1];

	//запись программы в виртуальную память, первый 2 байта пропускаем
	std::copy(codeArray[2], codeArray[ptr], memory[getRegister(Help::CS).getValue() << 4]);

	int t = getRegister(Help::DS).getValue() << 4;

	std::copy(codeArray[ptr], codeArray[length], memory[getRegister(Help::DS).getValue() << 4]);

	

	//установка регистров
	getRegister(Help::SS).setValue(0x2000); // основной регистр стека
	getRegister(Help::IP).setValue(0); // счётчик(регистр) команд
	getRegister(Help::SP).setValue(0); // указатель на вершину стека

	deb.setCode(this);
	setZeroFlag(false);
	setGreaterFlag(false);
	setExitProgram(false);



}

void Code::Run()
{
	//цикл(т.е программа) выполняется до тех пор, пока счётчик команд не пересечёт границу DS, т.е данных
	while( !isExitProgram() )
	{
		//абcолютный адрес
		int addr = (getRegister(Help::CS).getValue() << 4) + getRegister(Help::IP).getValue();

		if (isDebug())
			deb.Update(addr);
		
		//заранее смещаем счётчик команд на 3(т.к каждая команда = 3 байта)
		getRegister(Help::IP) += 3;
		//получаем код команды
		byte operation = *memory[addr++];

		//считываем 2 байта - слово, эти данные передаются в команду
		RegisterWord reg;
		reg.setLeftRegister(*memory[addr++]);
		reg.setRightRegister(*memory[addr++]);

		//получаем соответствующий оператор
		AsmOperator *curOperator = AsmOperator::newOperator(operation);
		//выполняем оператор
		curOperator->Do(operation, *this, reg);
		//освобождаем память
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
