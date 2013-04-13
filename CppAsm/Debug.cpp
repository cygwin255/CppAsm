#include "Debug.h"

#include "Help.h"
#include "AsmOperator.h"
#include "Code.h"

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <utility>
#include <cctype>
#include <conio.h>
#include <windows.h>

using namespace std;


const char Debug::FILLER = static_cast<char>(176);
const char Debug::HORIZONTAL_BAR = static_cast<char>(196);
const char Debug::VERTICAL_BAR = static_cast<char>(179);


Debug::Debug()
{
	m_codeHeight = 13;
	m_dataHeight = 5;

	m_registersHeight = 3;
	m_dataOffset = 0;

	m_waitAddress = 0;
}

void Debug::Update(int codeOffset)
{
	if (m_waitAddress != 0 && m_waitAddress != codeOffset)
		return;

	m_waitAddress = 0;

	//очищаем поток и консоль
	ClearStream();

	DrawRegistersState();

	DrawCodeAndStackState(codeOffset);

	DrawDataState();

	m_stream << "          <F10 = Step> <F11 = Step IN> <Up|down = data move>";

	//выводим буферный вывод в консоль
	printf("%s", m_stream.str().c_str());
	
	HandleKeyPress(codeOffset);
}

void Debug::ClearStream()
{
	system("cls");
	m_stream.str( string() );
	m_stream.clear();
}

void Debug::DrawRegistersState()
{
	typedef std::pair<const char *, const RegisterWord *> regpair;
	//массив регистров, кроме половин
	regpair registers[50];
	//размер массива регистров
	int reg_size = 0;
	//поиск нужных регистров, байтовые регистры(ah, cl..) не включаем
	for(int i=0;i<Help::doubleArrayLength(AsmOperator::Registers);i++)
	{
		switch(i)
		{
		case 0x01:
		case 0x02:
		case 0x04:
		case 0x05:
		case 0x07:
		case 0x08:
		case 0x0A:
		case 0x0B:
			continue;
		default:
			registers[reg_size++] = std::make_pair( AsmOperator::Registers[i], &m_code->getRegister(i) );
		}
	}
	//прописны буквы
	m_stream << uppercase;
	//состояния регистров по строкам и столбцам
	for(int i=0;i<m_registersHeight;i++)
	{
		for(int j=0;j<reg_size;j++)
			if (j % m_registersHeight == i)
				m_stream << setw(3) << left << setfill(' ') << registers[j].first 
				<< setw(4) << right << setfill('0') << hex  << registers[j].second->getValue()
				<< ' ' << VERTICAL_BAR << ' ';
		if (i == 0)
		{
			m_stream << "ZF " << noboolalpha << m_code->isZeroFlag() << " " << VERTICAL_BAR << " ";
			m_stream  << "GF " << noboolalpha << m_code->isGreaterFlag();
		}

		m_stream << endl;
	}
	m_stream << setfill(HORIZONTAL_BAR) << setw(60) << HORIZONTAL_BAR 
		<< static_cast<char>(194) << setw(19) << HORIZONTAL_BAR;
}

void Debug::DrawCodeAndStackState(int codeOffset)
{
	//текущий оператор
	int current_op = codeOffset;

	//плавное перемещение на 4 позицию
	for(int i=0;i < (m_codeHeight/2) && codeOffset > 0;i++)
		codeOffset -= 3;

	//адрес вершины стека
	int stack_head_max = m_code->getRegister(Help::SP).getValue();
	
	int stack_head = stack_head_max - m_codeHeight*2;
	if (stack_head < 0)
		stack_head = 0;


#pragma region code + stack
	for(int i=0;i<m_codeHeight;i++)
	{
		//адрес
		m_stream << hex << setw(4) << setfill('0') << m_code->getRegister(Help::CS).getValue() << ':'
			<< hex << setw(4) << setfill('0') << (codeOffset - m_code->getRegister(Help::CS).getValue())
			<< setw(6) << (current_op == codeOffset ? setfill(FILLER) : setfill(' ')) << ' ';

		byte command[3];
		//считываем команду из памяти
		m_code->memory.read(codeOffset, command, 3);
		RegisterWord r;
		r.setLeftRegister(command[1]);
		r.setRightRegister(command[2]);

		bool smallRegister = r.getValue() <= 0xFF;
		int registerWidth = smallRegister ? 2 : 4;
		//проверяем на достищения сегмента данных, которые следует сразу после сегмента команд
		if (codeOffset >= m_code->getRegister(Help::DS).getValue())
		{
			m_stream << "   DATA SEGMENT";

			m_stream << setw(31) << setfill(' ') << VERTICAL_BAR << " ";
		}
		else
		{
			//выводим тип оператора
			m_stream << setw(6) << left << (current_op == codeOffset ? setfill(FILLER) : setfill(' ')) 
				<< AsmOperator::Operators[command[0]];
			//проверка на ссылки, когда следует заменять операнд команды на соответствующий регистр
			if (Help::isOnlyNumericOperator(command[0]))
				m_stream << setw(registerWidth) << right << setfill('0') << r.getValue();
			else
				m_stream << setw(registerWidth) << right << (current_op == codeOffset ? setfill(FILLER) : setfill(' ')) 
				<< AsmOperator::Registers[command[2]];
			//отступ для вывода стека
			m_stream << (current_op == codeOffset ? setfill(FILLER) : setfill(' ')) << setw(38 - registerWidth + 2) 
				<< VERTICAL_BAR << " ";
		}
			if (stack_head < stack_head_max)
			{
				//адрес стека
				m_stream << '+' << setw(4) << setfill('0') << stack_head << setfill(' ') << setw(2) << ' ';

				byte heap[2];
				//считываем 2 байта стека из памяти
				m_code->memory.read(m_code->getRegister(Help::SS).getValue() + stack_head, heap, 2);
				RegisterWord r;
				r.setLeftRegister(heap[0]);
				r.setRightRegister(heap[1]);

				m_stream << setw(4) << right << setfill('0') << r.getValue();

				stack_head += 2;
			}
			else if (i == 0) 
				m_stream << "empty";
			m_stream << endl;
		
		//смещаем указатель на следующую команду в памяти (размер команда = 3)
		codeOffset += 3;
	}
#pragma endregion code + stack

	m_stream << setfill(HORIZONTAL_BAR) << setw(60) << HORIZONTAL_BAR 
		<< static_cast<char>(197) << setw(19) << HORIZONTAL_BAR;
}

void Debug::DrawDataState()
{

	int dataAddr = m_dataOffset;

#pragma region data segment
	for(int i=0;i<m_dataHeight + 1;i++)
	{
		if (i == 0)
		{
			m_stream << setw(9) << setfill(' ') << ' ';
			for(int j=0;j<16;j++)
			{
				m_stream << setw(3) << right << hex << j;
				if (j == 7) m_stream << "  ";
			}
			m_stream << " " << VERTICAL_BAR << endl;
			continue;
		}

		m_stream << "DS:" << hex << setw(4) << setfill('0') << dataAddr << "   ";

		for(int j=0;j<16;j++)
		{
			byte buffer[1];

			m_code->memory.read(m_code->getRegister(Help::DS).getValue() + dataAddr + j, buffer, 1);

			m_stream << hex << setfill('0') << setw(2) << (int)buffer[0] << ' ';
			if (j == 7)
				m_stream << "  ";
		}

		m_stream << VERTICAL_BAR << " ";

		for(int j=0;j<16;j++)
		{
			byte buffer[1];

			m_code->memory.read(m_code->getRegister(Help::DS).getValue() + dataAddr + j, buffer, 1);
			if (!isprint(buffer[0]))
				buffer[0] = '.';
			m_stream << (char)buffer[0];

			if (j == 7)
				m_stream << " ";
		}

		m_stream << endl;

		dataAddr += 16;
	}
#pragma endregion data segment
}

void Debug::HandleKeyPress( int codeOffset)
{
	static bool alreadyInCycle = false;
	static const int F10 = 68;
	static const int F11 = 133;
	static const int UP = 72; // стрелка вверх
	static const int DOWN = 80; // стрелка вниз


	if (!alreadyInCycle)
		while(true)
		{
			alreadyInCycle = true;
			Sleep(50);

			int key = _getch();
			if (key == 0 || key == 224)
				key = _getch();


			switch(key)
			{
			case F10: 
				alreadyInCycle = false;
				m_waitAddress = codeOffset + 3;
				return;

			case F11: // F11
				alreadyInCycle = false;
				return;

			case UP: 
				if ((m_dataOffset -= 16) < 0) 
					m_dataOffset = 0;

				Update(codeOffset);
				break;

			case DOWN:
				int max_scroll = m_code->memory.getSize() - m_dataHeight*16;
				if ((m_dataOffset += 16) > max_scroll) 
					m_dataOffset = max_scroll;

				Update(codeOffset);
				break;
			}
		}
}