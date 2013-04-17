#include "CodeArray.h"

#include <iterator>

CodeArray::CodeArray()
	: current(0)
{
	//lines = new char *[65535];	
}

CodeArray::~CodeArray()
{
//	for (int i=0;i<current;i++)
	//	delete [] lines[i];

//	delete [] lines;
}

void CodeArray::Add(byte c)
{
	lines[current++] = c;
}

void CodeArray::Add(char c, const RegisterWord &reg)
{
	Add(c);
	Add(reg.getLeftRegister());
	Add(reg.getRightRegister());
}

void CodeArray::Add(const char *ch, int len)
{
	for(int i=0;i<len;i++)
		Add(ch[i]);
}

char *CodeArray::operator[](int i)
{
	return &lines[i];
}

int CodeArray::getSize() const
{
	return current;
}

void CodeArray::SetAt(int position, byte c)
{
	lines[position] = c;
}
