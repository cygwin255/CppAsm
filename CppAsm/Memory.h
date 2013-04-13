#ifndef MEMORY_H
#define MEMORY_H

#include "defs.h"

class Memory
{
public:
	Memory(int = 65536);
	~Memory();
	
	char *operator[](int);

	void read(int , byte *, int);

	int getSize();

private:
	char *memory;
	int size;
};

#endif