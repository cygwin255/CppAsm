#include <cstdlib>
#include <time.h>

#include "Memory.h"
#include "defs.h"

Memory::Memory()
{
	memory = new char[Memory::size];

	//����� ��������� ���
	srand (time(NULL));

	//���������� ���������� ������ ������������� �������
	for(int i=0;i<Memory::size;++i)
		memory[i] = rand() % 256;
}

Memory::~Memory()
{
	delete [] memory;
}

char *Memory::operator[](size_t index)
{
	return &memory[index];
}

void Memory::read(size_t from, byte * buffer, size_t count)
{
	for(int i=0;i<count;i++)
		buffer[i] = memory[from + i];
}

size_t Memory::getSize()
{
	return size;
}
