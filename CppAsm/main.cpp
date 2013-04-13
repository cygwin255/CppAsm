#include <iostream>
#include <iomanip>

#include "Code.h"

#include "Compiler.h"
#include <conio.h>

//#include <time.h>


using namespace std;



int main(int argc, char *argv[])
{
#ifndef _DEBUG
	string s(argv[0]);
	s += ".obj";

	Compiler::getInstance()->Compile(argv[1], s.c_str());
	Code code(s.c_str());
#else
	Compiler::getInstance()->Compile("..\\Examples\\HelloWorld.casm", "..\\Examples\\HelloWorld.obj");
	Code code("..\\Examples\\HelloWorld.obj");
#endif
	
	code.setDebug(true);

	//long c1 = clock();
	code.Run();
	//long c2 = clock();

	//cout << (c2 - c1) << endl;

	cout << endl << "Press ESC to exit";
#ifndef _DEBUG
	while(_getch() != 27);
#endif

	return 0;
}