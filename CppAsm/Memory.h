#ifndef MEMORY_H
#define MEMORY_H

#include "defs.h"

class Memory
{
public:
	Memory(int = 65536);
	~Memory();
	
	char *operator[](size_t);

	void read(size_t , byte *, size_t);

	size_t getSize();

private:
	char *memory;
	size_t size;
};

#endif