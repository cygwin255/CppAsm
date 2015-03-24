#ifndef MEMORY_H
#define MEMORY_H

#include "defs.h"

class Memory
{
public:
	Memory();
	~Memory();
	
	char *operator[](size_t);

	void read(size_t , byte *, size_t);

	size_t getSize();

private:
	char *memory;
	static const size_t size = 1048560;
};

#endif