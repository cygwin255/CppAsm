#ifndef REGISTERWORD_H
#define REGISTERWORD_H


#include "defs.h"

class RegisterWord
{
public:
	RegisterWord(word = 0);

	byte getLeftRegister() const;
	byte getRightRegister() const;
	word getValue() const;

	void setLeftRegister(byte reg);
	void setRightRegister(byte reg);
	void setValue(word w);

	const RegisterWord &operator+=(const RegisterWord &reg)
	{
		setValue(getValue() + reg.getValue());
		return *this;
	}
	const RegisterWord &operator-=(const RegisterWord &reg)
	{
		setValue(getValue() - reg.getValue());
		return *this;
	}
	const RegisterWord &operator*=(const RegisterWord &reg)
	{
		setValue(getValue() * reg.getValue());
		return *this;
	}
	const RegisterWord &operator/=(const RegisterWord &reg)
	{
		setValue(getValue() / reg.getValue());
		return *this;
	}
	const RegisterWord &operator%=(const RegisterWord &reg)
	{
		setValue(getValue() % reg.getValue());
		return *this;
	}
	const RegisterWord &operator=(const RegisterWord &reg)
	{
		setValue(reg.getValue());
		return *this;
	}
	int leftright;
private:
	word value;
};

#endif