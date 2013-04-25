#include "AsmOperator.h"

#include "ADD.h"
#include "CMP.h"
#include "DEC.h"
#include "INC.h"
#include "INT.h"
#include "JMP.h"
#include "JNZ.h"
#include "JZ.h"
#include "LOOP.h"
#include "MOV.h"
#include "NOP.h"
#include "POP.h"
#include "PUSH.h"
#include "RET.h"
#include "SUB.h"
#include "MUL.h"
#include "DIV.h"
#include "MGET.h"
#include "MSET.h"
#include "CALL.h"
#include "MOD.h"


#include "defs.h"

using namespace std;

const char *AsmOperator::Operators[] = { "mov", "add", "sub", "inc", "dec", "int","loop", "jmp", "ret",
	"push", "push", "pop", "nop", "cmp", "jz", "jnz", "mul", "div", "mget", "mset", "call", "mod", "" };

 const char *AsmOperator::Registers[] = { "ax", "ah", "al", "bx", "bh", "bl", "cx", "ch", "cl", "dx", 
 	"dh", "dl", "sp", "bp", "si", "di", "cs", "ds", "ss", "es", "ip", "" };

AsmOperator::AsmOperator()
{
}

AsmOperator *AsmOperator::newOperator(byte opcode)
{
	//TODO: переделать через статические переменные,
	//нет нужды каждый раз выделять память
	//и потом её освобождать
	AsmOperator *op;

#pragma region switch
	switch(opcode)
	{
	case Help::MOV: 
		op =  new OpMov();
		break;
	case Help::ADD: 
		op =  new OpAdd();
		break;
	case Help::SUB: 
		op =  new OpSub();
		break;
	case Help::INC: 
		op =  new OpInc();
		break;
	case Help::DEC: 
		op =  new OpDec();
		break;
	case Help::INT: 
		op =  new OpInt();
		break;
	case Help::LOOP :
		op =  new OpLoop();
		break;
	case Help::JMP: 
		op =  new OpJmp();
		break;
	case Help::RET: 
		op =  new OpRet();
		break;
	case Help::PUSH: 
	case Help::PUSH_ALT: 
		op =  new OpPush();
		break;
	case Help::POP: 
		op =  new OpPop();
		break;
	case Help::NOP: 
		op =  new OpNop();
		break;
	case Help::CMP: 
		op =  new OpCmp();
		break;
	case Help::JZ: 
		op =  new OpJz();
		break;
	case Help::JNZ: 
		op =  new OpJnz();
		break;
	case Help::MUL:
		op = new OpMul();
		break;
	case Help::DIV:
		op = new OpDiv();
		break;
	case Help::MGET:
		op = new OpMget();
		break;
	case Help::MSET:
		op = new OpMset();
		break;
	case Help::CALL:
		op = new OpCall();
		break;
	case Help::MOD:
		op = new OpMod();
		break;
	}
#pragma endregion switch

	return op;
}