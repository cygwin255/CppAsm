#ifndef REGISTER_HPP
#define REGISTER_HPP

#include "defs.h"
#include <iostream>

using namespace std;

template <typename T>
class Register
{
	template<typename T>
	friend ostream &operator<<(ostream &, const Register<T> &);
public:
	Register(T = 0);

	inline T getValue() const;
	inline void setValue(T b);
	
	Register operator+(const Register &);
	Register operator-(const Register &);

	Register operator*(const Register &);
	Register operator/(const Register &);

	bool operator<(const Register &);
	bool operator>(const Register &);

	bool operator==(const Register &);
	bool operator!=(const Register &reg)
	{
		return !(*this == reg);
	}

	const Register &operator=(const Register &);

private:
	T value;
};


template <typename T>
Register<T>::Register(T in)
	: value(in)
{
}

template <typename T>
T Register<T>::getValue() const
{
	return value;
}

template <typename T>
void Register<T>::setValue(T b)
{
	value = b;
}

template <typename T>
Register<T> Register<T>::operator+(const Register<T> &reg)
{
	return Register(getValue() + reg.getValue());
}

template <typename T>
Register<T> Register<T>::operator-(const Register<T> &reg)
{
	return Register(getValue() - reg.getValue());
}

template <typename T>
Register<T> Register<T>::operator*(const Register<T> &reg)
{
	return Register(getValue() * reg.getValue());
}

template <typename T>
Register<T> Register<T>::operator/(const Register<T> &reg)
{
	return Register(getValue() / reg.getValue());
}

template <typename T>
bool Register<T>::operator<(const Register &reg)
{
	return getValue() < reg.getValue();
}

template <typename T>
bool Register<T>::operator>(const Register &reg)
{
	return getValue() > reg.getValue();
}

template <typename T>
const Register<T> &Register<T>::operator=(const Register<T> &reg)
{
	setValue(reg.getValue());
	return *this;
}

template <typename T>
bool Register<T>::operator==(const Register &reg)
{
	return getValue() == reg.getValue();
}

template <typename T>
ostream &operator<<(ostream &output, const Register<T> &reg)
{
	output << static_cast<int>(reg.getValue());
	return output;
}


#endif