#ifndef BYTECODE_INSTRUCTION_H
#define BYTECODE_INSTRUCTION_H

#include "opcode.h"
#include "valuetype.h"
#include "stackvalue.h"

using namespace std;

namespace bytecode
{
	struct instruction
	{
	public:
		instruction();
		instruction(opcode opcode, valuetype dataType, stackvalue data);
		opcode code;
		stackvalue data;
		valuetype dataType;
	};
}
#endif
