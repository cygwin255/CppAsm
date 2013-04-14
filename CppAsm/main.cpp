#include <iostream>
#include <iomanip>

#include "Code.h"

#include "Compiler.h"
#include <conio.h>

using namespace std;


int main(int argc, char *argv[])
{
#ifndef _DEBUG

	//проверяем правильность аргументов
	if (argc == 1)
	{
		//если неправильное количество, то выводим подсказку
		cout << "Invalid input parametes" << endl;
		cout << "usage: cppasm.exe -path <path> [-compile] [-run] [-debug]" << endl;
		cout << "default flags: -compile -run" << endl << endl;
		cout << "    -compile\tcompile program" << endl;
		cout << "    -run\trun program" << endl;
		cout << "    -debug\trun debugger" << endl;

		system("pause");
		return 1;
	}

	//определяем стандартные пути для загрузки и исполнения
	string path = "";
	string out_path = path;
	out_path += ".obj";

	//флаги
	bool compile = false;
	bool run = false;
	bool debug = false;

	if (argc == 3)
	{
		//флаги по умолчанию
		compile = true;
		run = true;
		debug = false;

		path = string(argv[2]);
	}
	else
	{
		//иначе ищем включенные флаги
		for(int i=0;i<argc;i++)
			if (string(argv[i]) == "-compile")
				compile = true;
			else if (string(argv[i]) == "-run")
				run = true;
			else if (string(argv[i]) == "-debug")
				debug = true;
			else if (string(argv[i]) == "-path")
				path = string(argv[i + 1]);

		//если выставлен только запуск, то переопределяем путь
		if (!compile && run)
			out_path = path;
	}

	//проверяем отсутствие -path
	if(path.size() == 0)
	{
		cout << "Error! -path not found" << endl;
		return 1;
	}

	//компиляция в байт-код
	if (compile)
		Compiler::getInstance()->Compile(path.c_str(), out_path.c_str());

	//исполнение байт-кода
	if (run)
	{
		Code code(out_path.c_str());
		code.setDebug(debug);
		code.Run();
	}
#else
	Compiler::getInstance()->Compile("..\\Examples\\HelloWorld.casm", "..\\Examples\\HelloWorld.obj");
	Code code("..\\Examples\\HelloWorld.obj");
	code.Run();
#endif
	

	
	cout << endl << "Press ESC to exit";
#ifndef _DEBUG
	while(_getch() != 27);
#endif
	
	return 0;
}