#ifndef STACK_H
#define STACK_H

#include "defs.h"

class Stack
{
public:
	Stack(int = 128);
	Stack(const Stack &);
	~Stack();

	void push(word);
	void pop(word &);

private:
	word *Ptr;
	int top;
};

#endif