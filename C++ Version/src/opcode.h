#ifndef BYTECODE_OPCODES_H
#define BYTECODE_OPCODES_H

namespace bytecode
{
	enum opcode
	{
		NOP,
		PUSH,
		ST,
		LD,

		MUL,
		DIV,
		ADD,
		SUB,
		MOD,
		EQ,
		NEQ,

		JMP,

		BRFALSE,
		BRTRUE,

		BRLT,
		BRLE,

		COMP,

		INC,
		DEC,

		CALL,
		RET,

		SET,

		ADD_1,
		LD_2
	};
};
#endif
