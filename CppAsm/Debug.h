#ifndef DEBUG_H
#define DEBUG_H

class Code;

#include <sstream>

using namespace std;

class Debug
{
public:
	Debug();

	void Update(int);

	Code *getCode() const { return m_code; }
	void setCode(Code *val) { m_code = val; }

private:
	ostringstream m_stream;
	Code *m_code;

	int m_waitAddress;

	int m_registersHeight;

	int m_codeHeight;

	int m_dataOffset;
	int m_dataHeight;

	static const char VERTICAL_BAR;
	static const char HORIZONTAL_BAR;
	static const char FILLER;

	void ClearStream();

	void DrawRegistersState();
	void DrawCodeAndStackState(int);
	void DrawDataState();
	void HandleKeyPress(int);
};

#endif