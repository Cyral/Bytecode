#include "instruction.h"

namespace bytecode {
	instruction::instruction()
	{
	}
	instruction::instruction(opcode opcode, valuetype dataType, stackvalue* data)
	{
		instruction::code = opcode;
		instruction::dataType = dataType;
		instruction::data = data;
	}
}
