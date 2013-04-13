#include "Memory.h"
#include "defs.h"

Memory::Memory(int size)
{
	Memory::size = size > 0 ? size : 65536;
	memory = new char[Memory::size]();
}

Memory::~Memory()
{
	delete [] memory;
}

char *Memory::operator[](int index)
{
	return &memory[index];
}

void Memory::read(int from, byte * buffer, int count)
{
	for(int i=0;i<count;i++)
		buffer[i] = memory[from + i];
	
}

int Memory::getSize()
{
	return size;
}
