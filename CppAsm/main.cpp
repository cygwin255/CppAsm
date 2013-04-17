#include <iostream>
#include <iomanip>
#include <conio.h>


#include "Code.h"
#include "Compiler.h"
#include "CmdLineArgHelper.h"

using namespace std;


void printHelpMsg()
{
	cout << "Invalid input parametes" << endl;
	cout << "usage: cppasm.exe -path <path> [-compile] [-run] [-debug]" << endl;
	cout << "default flags: -compile -run" << endl << endl;
	cout << "    -compile\tcompile program" << endl;
	cout << "    -run\trun program" << endl;
	cout << "    -debug\trun debugger" << endl;
}


int main(int argc, char **argv)
{
#ifndef _DEBUG



	//проверяем правильность аргументов
	if (argc == 1)
	{
		//если неправильное количество, то выводим подсказку
		printHelpMsg();
		system("pause");
		return 0;
	}

	//определяем стандартные пути для загрузки и исполнения
	string path(CmdLineArgHelper::findFlagParameter(argc, argv, "-path"));
	string out_path = path;
	out_path += ".obj";

	//флаги
	bool compile = CmdLineArgHelper::findFlag(argc, argv, "-compile");
	bool run = CmdLineArgHelper::findFlag(argc, argv, "-run");
	bool debug = CmdLineArgHelper::findFlag(argc, argv, "-debug");


	if (!compile)
	{
		if (run)
			out_path = path; //если выставлен только запуск, то переопределяем путь запуска
		else // или если флаги сняты
			compile = run = true; // то, по умолчанию, включаем их
	}
	
	if (!CmdLineArgHelper::isFileExists(path.c_str()))
	{
		cout << "File " << path << " not found!";
		system("pause");
		return 0;
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