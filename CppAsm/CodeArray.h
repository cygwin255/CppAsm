#ifndef CODEARRAY_H
#define CODEARRAY_H

#include "RegisterWord.h"

class CodeArray
{
public:
	CodeArray();
	~CodeArray();

	void Add(byte);
	void Add(char, const RegisterWord &);
	void Add(const char *, int);

	void SetAt(int, byte);

	

	int getSize() const;

	char *operator[](int);
//private:
	char lines[1024*128];
	int current;
};

#endif