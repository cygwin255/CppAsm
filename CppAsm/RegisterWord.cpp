#include "RegisterWord.h"



RegisterWord::RegisterWord(word in)
{
	leftright = 0;
	setValue(in);
}

byte RegisterWord::getLeftRegister() const
{
	return static_cast<byte>(value / 0x100);
}

byte RegisterWord::getRightRegister() const
{
	return static_cast<byte>(value % 0x100);
}

void RegisterWord::setLeftRegister( byte reg )
{
	if (leftright == 1)
		return setRightRegister(reg);

	value = static_cast<word>(reg * 0x100 + getRightRegister());
}

void RegisterWord::setRightRegister( byte reg )
{
	if (leftright == -1)
		return setLeftRegister(reg);

	value = static_cast<word>(getLeftRegister() * 0x100 + reg);
}

void RegisterWord::setValue( word w )
{
	if (leftright == -1)
		setLeftRegister(w % 0x100);
	else if (leftright == 1)
		setRightRegister(w % 0x100);
	else
		value = w;
}

word RegisterWord::getValue() const
{
	if (leftright == -1)
		return getLeftRegister();

	if (leftright == 1)
		return getRightRegister();

	return value;
}
