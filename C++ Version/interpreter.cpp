#include <map>
#include <vector>
#include <iostream>
#include "interpreter.h"
#include "parser.h"
#include "opcode.h"
#include "instruction.h"
#include "stackvalue.h"
#include "valuetype.h"

using namespace std;

namespace bytecode {
interpreter::interpreter(vector<string> lines)
{
		interpreter::lines = lines;
		interpreter::parser = new bytecode::parser();
		interpreter::locals = map<int, stackvalue>();
		interpreter::stack = faststack();
}

void interpreter::run() {
		auto parserResult = interpreter::parser->run(interpreter::lines);
		auto optimizedResult = parserResult;//optimizer.Run(parserResult);
		auto instructions = optimizedResult->instructions;
		auto jumptable = optimizedResult->jumptable;

		int from = 0;
		int total = 0;
		const int num = instructions.size();
		const instruction* ptr = instructions.data();
		for (int ip = 0; ip < num; ip++)
		{
				auto const instruction = &ptr[ip];

				total++;

				switch (instruction->code)
				{

				case opcode::PUSH:
						stack.push(instruction->data);
						break;

				case opcode::ST:
				{
						locals[instruction->data.get_int()] = stack.pop();
						break;
				}
				case opcode::LD:
				{
						stack.push(locals[instruction->data.get_int()]);
						break;
				}
				case opcode::INC:
				{
						const auto index = instruction->data.get_int();
						locals[index] = stackvalue(locals[index].get_int() + 1);
						break;
				}
				case opcode::DEC:
				{
						const auto index = instruction->data.get_int();
						locals[index] = stackvalue(locals[index].get_int() - 1);
						break;
				}
				case opcode::MUL:
						stack.mul();
						break;
				case opcode::DIV:
						stack.div();
						break;
				case opcode::ADD:
						stack.add();
						break;
				case opcode::SUB:
						stack.sub();
						break;
				case opcode::MOD:
						stack.mod();
						break;
				case opcode::BRLT:
				{
						const int val2 = stack.pop().get_int();
						if (stack.pop().get_int() < val2)
						{
								from = ip;
								ip = jumptable[instruction->data.get_int()];
						}
						break;
				}
				case opcode::BRLE:
				{
						const int val2 = stack.pop().get_int();
						if (stack.pop().get_int() <= val2)
						{
								from = ip;
								ip = jumptable[instruction->data.get_int()];
						}
						break;
				}
				case opcode::BRFALSE:
				{
						if (!stack.pop().get_bool())
						{
								from = ip;
								ip = jumptable[instruction->data.get_int()];
						}
						break;
				}
				case opcode::BRTRUE:
				{
						if (stack.pop().get_bool())
						{
								from = ip;
								ip = jumptable[instruction->data.get_int()];
						}
						break;
				}
				case opcode::JMP:
				{
						from = ip;
						ip = jumptable[instruction->data.get_int()];

						break;
				}

				case opcode::CALL:
				{
						//	stack.pop();
						//break;

						string function = instruction->data.get_string();
						if (function == "print")
						{
								cout << stack.pop().get_string() << endl;
						}
						break;
				}

				case opcode::RET:
						ip = from;
						break;

				}
		}

		cout << endl << total << " instructions executed." << endl;
		return;
}
}
