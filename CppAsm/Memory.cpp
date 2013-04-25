#include <cstdlib>
#include <time.h>

#include "Memory.h"
#include "defs.h"

Memory::Memory(int size)
{
	Memory::size = size > 0 ? size : 65536;
	memory = new char[Memory::size];

	//задаём случайный сид
	srand (time(NULL));

	//симулируем заполнение памяти произвольными данными
	for(int i=0;i<size;++i)
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
