#ifndef STRHELP_H
#define STRHELP_H


#include <cstring>
#include <cmath>
#include <exception>
#include <vector>

#include "RegisterWord.h"
#include "Code.h"

class Help
{
public:

	static const char MOV = 0x00;
	static const char ADD = 0x01;
	static const char SUB = 0x02;
	static const char INC = 0x03;
	static const char DEC = 0x04;
	static const char INT = 0x05;
	static const char LOOP = 0x06;
	static const char JMP = 0x07;
	static const char RET = 0x08;
	static const char PUSH = 0x09;
	static const char PUSH_ALT = 0x0A;
	static const char POP = 0x0B;
	static const char NOP = 0x0C;
	static const char CMP = 0x0D;
	static const char JZ = 0x0E;
	static const char JNZ = 0x0F;
	static const char MUL = 0x10;
	static const char DIV = 0x11;
	static const char MGET = 0x12;
	static const char MSET = 0x13;
	static const char CALL = 0x14;
	static const char MOD = 0x15;

	static const char AX = 0x00;
	static const char AH = 0x01;
	static const char AL = 0x02;
	static const char BX = 0x03;
	static const char BH = 0x04;
	static const char BL = 0x05;
	static const char CX = 0x06;
	static const char CH = 0x07;
	static const char CL = 0x08;
	static const char DX = 0x09;
	static const char DH = 0x0A;
	static const char DL = 0x0B;
	static const char SP = 0x0C;
	static const char BP = 0x0D;
	static const char SI = 0x0E;
	static const char DI = 0x0F;
	static const char CS = 0x10;
	static const char DS = 0x11;
	static const char SS = 0x12;
	static const char ES = 0x13;
	static const char IP = 0x14;
	

	static int HexCharToInt(char c)
	{
		if (c - '0' < 10)
			return c - '0';
		switch(c)
		{
		case 'a':
		case 'A':
			return 10;
		case 'b':
		case 'B':
			return 11;
		case 'c':
		case 'C':
			return 12;
		case 'd':
		case 'D':
			return 13;
		case 'e':
		case 'E':
			return 14;
		case 'f':
		case 'F':
			return 15;
		}

		return -1;
	}

	static int doubleArrayLength(const char *arr[])
	{
		int i = 0;
		while(arr[i][0] != '\0')
			i++;

		return i;
	}

	static int findInArray(const char *arr[], const char *str)
	{
		for(int i=0;i<doubleArrayLength(arr);i++)
			if (!strcmp(arr[i], str))
				return i;

		return -1;
	}

	static word parseNum(const char *str)
	{
		int len = strlen(str);
		bool hex = str[len - 1] == 'h';

		word num = 0;

		for (int i=0;i<len - hex;i++)
			num += static_cast<word>(HexCharToInt(str[i]) * pow(hex ? 16.0 : 10.0, len - hex - i - 1));

		return num;
	}

	static longint CRC32(const char *str)
	{
		int len = strlen(str);

		longint crc_table[256];
		longint crc;

		for (int i = 0; i < 256; i++)
		{
			crc = i;
			for (int j = 0; j < 8; j++)
				crc = crc & 1 ? (crc >> 1) ^ 0xEDB88320UL : crc >> 1;
			crc_table[i] = crc;
		}

		crc = 0xFFFFFFFFUL;
		while (len--)
			crc = crc_table[(crc ^ *str++) & 0xFF] ^ (crc >> 8);

		return crc ^ 0xFFFFFFFFUL;
	}

	static void getWordFromStack(Code &code, RegisterWord &r)
	{
		int addr = code.getRegister(Help::SS).getValue() + code.getRegister(Help::SP).getValue();

		r.setRightRegister(*code.memory[addr - 1]);
		r.setLeftRegister(*code.memory[addr - 2]);
		code.getRegister(Help::SP) -= 2;
	}

	static void putWordToStack(Code &code, const RegisterWord &reg)
	{
		int addr = code.getRegister(Help::SS).getValue() + code.getRegister(Help::SP).getValue();

		*code.memory[addr++] = reg.getLeftRegister();
		*code.memory[addr] = reg.getRightRegister();

		code.getRegister(Help::SP) += 2;
	}

	static bool isOnlyNumericOperator(byte op)
	{
		return op == Help::INT ||op == Help::PUSH_ALT || op == Help::CALL || op == Help::CALL || op == Help::JZ || op == Help::JNZ || op == Help::JMP || op == Help::LOOP;
	}

};
#endif