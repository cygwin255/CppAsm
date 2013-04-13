#include "Compiler.h"
#include "CodeArray.h"
#include "defs.h"
#include "Help.h"
#include "AsmOperator.h"

#include <fstream>
#include <regex>
#include <map>
#include <cstring>
#include <cstdlib>
#include <sstream>
#include <list>

using namespace std;

Compiler *Compiler::_instance = 0;

const int Compiler::COMMAND_REGEX_INDEX = 1;
const int Compiler::LEFT_OPERAND_REGEX_INDEX = 2;
const int Compiler::RIGHT_OPERAND_REGEX_INDEX = 5;
const int Compiler::LABEL_COMMAND_REGEX_INDEX = 6;

const int Compiler::DATA_LABEL_REGEX_INDEX = 1;
const int Compiler::DATA_TYPE_REGEX_INDEX = 2;
const int Compiler::DATA_DATA_REGEX_INDEX = 3;
const int Compiler::DATA_TEXT_REGEX_INDEX = 4;
const int Compiler::DATA_ARRAY_REGEX_INDEX = 7;

const int Compiler::USES_REGEX_INDEX = 3;


const int Compiler::BUFFER_SIZE = 256;

const regex Compiler::COMMAND_PARSE_REGEX("^[ \t]*([a-zA-Z]+) *([0-9a-fA-F]{2,}(h|[ \t]*$)?|[a-zA-Z0-9_-]{2,}|[ \t]*$)([ \t]*,[ \t]*([a-zA-Z]{2}|[0-9a-fA-F]+h?|\\[([a-zA-Z0-9]+)\\][ \t]*$)|[ \t]*$)");
const regex Compiler::LABEL_PARSE_REGEX("^[ \t]*([a-zA-Z0-9_-]{1,}): *$");
const regex Compiler::DATA_PARSE_REGEX("^[ \t]*([a-zA-Z0-9]+)[ \t]*d(b|w)[ \t]*('(.+)'|([a-fA-F0-9]+h{0,}[ \t]*(,| *$)+[ \t]*)+|\\[([a-fA-F0-9]+h?)\\])[ \t]*$");
const regex Compiler::DATA_ARRAY_PARSE_REGEX("[a-fA-F0-9]*h?");
const regex Compiler::REMOVE_COMMENTS_REGEX("[ \t]*(;|$).*");

const regex Compiler::USES_PARSE_REGEX("^[ \t]*([^:, ]+)([ \t]*uses(([ \t]*[a-z]{2}[ \t]*[,:][ \t]*)+)|:[ \t]*)");
const regex Compiler::OPERATORS_LIST_PARSE_REGEX("[a-z]{2}");


Compiler *Compiler::getInstance()
{
	if (_instance == 0)
		_instance = new Compiler();

	return _instance;
}

//regular members:

Compiler::Compiler()
{
}

int Compiler::Compile( const char *LoadPath, const char *SavePath)
{
	//объявляем представление программы(объектного кода)
	CodeArray codeArray;

	//первое слово - указатель на сегмент данных, а пока резервируем место
	codeArray.Add(0);
	codeArray.Add(0);

	char line[BUFFER_SIZE];

	std::istringstream Input;

	readFile(LoadPath, Input);

	//лист для восстановления значений uses регистров при вызове ret
	list<RegisterWord> usesParams;

	//метки для переходов
	map<longint, int> labels;

	//метки(ссылки) на данные
	map<longint, int> dataLabels;

	//прямые данные для последующей записи в файл
	string rawData;

	//парсим все данные
	parseAllData(LoadPath, dataLabels, rawData);

	//парсим все метки
	parseAllLabels(LoadPath, labels);


	while (!Input.eof())
	{
		Input.getline(line, BUFFER_SIZE, '\n');

		smatch match_result;

		string s(line);

		s = regex_replace(s, REMOVE_COMMENTS_REGEX, string(""));

		regex_match (s.cbegin(), s.cend(), match_result, COMMAND_PARSE_REGEX);
		if (match_result.empty())
		{
			parseUses(line, codeArray, usesParams);
			continue;
		}

		bool isLabel = true;
		byte operation;
		RegisterWord leftRegister;
		RegisterWord rightRegister;

		bool altPush = false;

		//парсим код оператора
		operation = Help::findInArray(AsmOperator::Operators, match_result[COMMAND_REGEX_INDEX].str().c_str());
		//парсим левый операнд
		parseRegisters(match_result, leftRegister, LEFT_OPERAND_REGEX_INDEX, altPush, isLabel);
		//парсим правый операнд
		parseRegisters(match_result, rightRegister, RIGHT_OPERAND_REGEX_INDEX, altPush, isLabel);

		//получаем текущий оператор при помощи фабрики
		AsmOperator *curOperator = AsmOperator::newOperator(operation);
		//проверяем, не переход ли это, если да, то присваиваем левому регистру адрес для перехода
		if (isLabel && labels[Help::CRC32(match_result[LEFT_OPERAND_REGEX_INDEX].str().c_str())] != 0)
			leftRegister.setValue(labels[Help::CRC32(match_result[LEFT_OPERAND_REGEX_INDEX].str().c_str())]*3 - 3);

		//аналогично, но только для ссылки на данные
		if (dataLabels[Help::CRC32(match_result[LABEL_COMMAND_REGEX_INDEX].str().c_str())] != 0)
			rightRegister.setValue(dataLabels[Help::CRC32(match_result[LABEL_COMMAND_REGEX_INDEX].str().c_str())] - 1);

		//проверяем, не нужно ли дописать push'ы для восстановления регистров
		if (operation == Help::RET)
			while (usesParams.size() > 0)
			{
				AsmOperator *_curOperator = AsmOperator::newOperator(Help::POP);

				_curOperator->ProcessParsedLine(usesParams.front(), 0, codeArray, false);
				usesParams.pop_front();
				//освобождаем память
				delete _curOperator;
			}

		//записываем команду в объектный код
		curOperator->ProcessParsedLine(leftRegister, rightRegister, codeArray, altPush);

		//освобождаем память
		delete curOperator;
	}
	

	//устанавливаем указатель на сегмент данных
	RegisterWord offset(codeArray.getSize());
	codeArray.SetAt(0, offset.getLeftRegister());
	codeArray.SetAt(1, offset.getRightRegister());

	ofstream Output(SavePath, ios::out | ios::binary);
	//записываем код программы
	for (int i=0;i<codeArray.getSize();++i)
		Output.write(codeArray[i], 1);

	//записываем код данных
	for(int i=0;i<rawData.size();i++)
		Output.write(&rawData[i], 1);

	Output.close();

	return 1;
}

void Compiler::parseAllData(const char *path, map<longint, int> &dataLabels, string &rawData)
{
	ifstream Input;
	Input.open(path);

	rawData = "";
	char line[BUFFER_SIZE*16];
	int currentPtr = 0;

	while (!Input.eof())
	{
		Input.getline(line, BUFFER_SIZE, '\n');

		smatch match_result;

		string s(line);
		s = regex_replace(s, REMOVE_COMMENTS_REGEX, string(""));

		regex_match (s.cbegin(), s.cend(), match_result, DATA_PARSE_REGEX);
		if (match_result.empty() || match_result[DATA_LABEL_REGEX_INDEX].str().length() == 0 || 
			match_result[DATA_DATA_REGEX_INDEX].str().length() == 0) 
			continue;

		longint _hash = Help::CRC32(match_result[DATA_LABEL_REGEX_INDEX].str().c_str());
		dataLabels[_hash] = currentPtr + 1;

		if (match_result[DATA_ARRAY_REGEX_INDEX].str().length() != 0) 
			parseNullDataArray(rawData, match_result, currentPtr);
		else if (match_result[DATA_TEXT_REGEX_INDEX].str().length() != 0) 
			parseDataString(rawData, match_result, currentPtr);
		else 
			parseFullDataArray(rawData, match_result, currentPtr);
	}

	Input.close();
}

void Compiler::parseNullDataArray(string &rawData, smatch &match_result, int &currentPtr)
{
	static const char Null_char = static_cast<char>(0);

	int count = Help::parseNum(match_result[DATA_ARRAY_REGEX_INDEX].str().c_str());

	if (match_result[DATA_TYPE_REGEX_INDEX].str()[0] == 'w') count *= 2;

	for(int i=0;i<count;i++)
		rawData += Null_char;
	currentPtr += count;
}

void Compiler::parseDataString(string &rawData, smatch &match_result, int &currentPtr)
{
	string str = regex_replace(match_result[DATA_TEXT_REGEX_INDEX].str(), regex("\\\\n"), string("\n"));
	rawData += str;
	currentPtr += str.size();
}

void Compiler::parseFullDataArray(string &rawData, smatch &match_result, int &currentPtr)
{
	string substring(match_result[DATA_DATA_REGEX_INDEX].str());
	static const sregex_token_iterator rend;
	sregex_token_iterator a(substring.begin(), substring.end(), DATA_ARRAY_PARSE_REGEX);

	while (a != rend) 
	{
		if ((*a).length() != 0)
		{
			RegisterWord r(Help::parseNum((*a).str().c_str()));

			if (match_result[DATA_TYPE_REGEX_INDEX].str()[0] == 'w')
			{
				rawData += r.getLeftRegister();
				currentPtr++;
			}

			rawData += r.getRightRegister();
			currentPtr++;
		}
		a++;
	}
}

void Compiler::parseAllLabels(const char *path, map<longint, int> &labels)
{
	ifstream Input;
	Input.open(path);

	char line[BUFFER_SIZE];

	int j = 0;
	int last_commas = 0;

	while (!Input.eof())
	{
		Input.getline(line, BUFFER_SIZE, '\n');

		smatch match_result;
		
		string s(line);
		//удаляем коментарии
		s = regex_replace(s, REMOVE_COMMENTS_REGEX, string(""));

		regex_match (s.cbegin(), s.cend(), match_result, USES_PARSE_REGEX);
		if (match_result[COMMAND_REGEX_INDEX].str().length() != 0)
		{ 
			//добавляем хэш надписи в мап, связываем его с адрессом команд
			longint _hash = Help::CRC32(match_result[COMMAND_REGEX_INDEX].str().c_str());
			labels[_hash] = j + 1;

			//вычисляем количество запятых, если они есть:
			int commas = 0;
			bool space = false;
			for(int i=0;i<s.size();i++)
				if (s[i] == ',') commas++;
			for(int i=0;i<s.size();i++)
				if (s[i] == ' ')
				{
					space = true;
					break;
				}
			//запятых, например 5, а разделяют они 6 элементов.
			if (commas > 0)
			{
				j += commas + 1;
				last_commas = commas + 1;
			}
			else if (space)
			{
				j++;
				last_commas = 1;
			}
			
			continue;
		}


		smatch math_result_cmd;

		s = line;
		s = regex_replace(s, REMOVE_COMMENTS_REGEX, string(""));

		regex_match (s.cbegin(), s.cend(), math_result_cmd, COMMAND_PARSE_REGEX);

		int operation = Help::findInArray(AsmOperator::Operators, math_result_cmd[COMMAND_REGEX_INDEX].str().c_str());

		if (operation == Help::RET)
			j += last_commas;

		if (math_result_cmd[COMMAND_REGEX_INDEX].str().length() != 0) 
			j++;
		if (math_result_cmd[RIGHT_OPERAND_REGEX_INDEX].str().length() != 0) 
			j++;
	}

	Input.close();
}

void Compiler::parseRegisters(const smatch &match, RegisterWord &reg, int index, bool &altPush, bool &isLabel)
{
	if (match[index].str().length() == 0) return;

	int reg_index = Help::findInArray(AsmOperator::Registers, match[index].str().c_str());
	isLabel = isLabel && (reg_index == -1);

	if (reg_index == -1)
	{
		reg = Help::parseNum(match[index].str().c_str());
		altPush = true;
	}
	else
		reg = reg_index;
}

void Compiler::readFile(const char *path, istringstream &stream)
{
	ifstream _Input(path);

	_Input.seekg (0, _Input.end);
	int length = _Input.tellg();
	_Input.seekg (0, _Input.beg);

	char *buffer = new char[length];

	_Input.read(buffer, length);
	_Input.close();

	stream = istringstream(string(buffer)); 

	delete [] buffer;
}

void Compiler::parseUses(const string &line, CodeArray &codeArray, list<RegisterWord> &usesParams)
{
	string toParse;
	
	smatch match_result;
	regex_match (line.cbegin(), line.cend(), match_result, USES_PARSE_REGEX);

	toParse = string(match_result[USES_REGEX_INDEX].str());

	if (match_result.empty() || toParse.size() == 0) 
		return;


	static const sregex_token_iterator rend;
	sregex_token_iterator a(toParse.begin(), toParse.end(), OPERATORS_LIST_PARSE_REGEX);

	while (a != rend) 
	{
		if (a->length() != 0)
		{
			string tr(a->str());

			int reg_index = Help::findInArray( AsmOperator::Registers, a->str().c_str() );
			
			if (reg_index == -1) exit(1);
			
			RegisterWord r(reg_index);
			usesParams.push_front(r);

			AsmOperator *curOperator = AsmOperator::newOperator(Help::PUSH);

			curOperator->ProcessParsedLine(r, 0, codeArray, false);

			//освобождаем память
			delete curOperator;

		}
		a++;
	}

}