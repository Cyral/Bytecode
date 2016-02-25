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
		interpreter::stack = vector<stackvalue>();
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
		for(int ip = 0; ip < num; ip++)
		{
				auto const instruction = *ptr[ip];

				total++;

				switch (instruction->code)
				{

				case opcode::PUSH:
						stack.push_back(stackvalue(instruction->data));
						break;

				case opcode::ST:
				{
						const int index = instruction->data.get_int();
						locals[index] = stackvalue(stack.back());
						stack.pop_back();
						break;
				}
				case opcode::LD:
				{
						const int index = instruction->data.get_int();
						stack.push_back(stackvalue(locals[index]));
						break;
				}

				case opcode::MUL:
				{
						const int val2 = stack.back().get_int();
						stack.pop_back();
						const int val1 = stack.back().get_int();
						stack.pop_back();
						stack.push_back(stackvalue(val1*val2));
						break;
				}

				case opcode::ADD:
				{
						const int val2 = stack.back().get_int();
						stack.pop_back();
						const int val1 = stack.back().get_int();
						stack.pop_back();
						stack.push_back(stackvalue(val1 + val2));
						break;
				}
				case opcode::SUB:
				{
						const int val2 = stack.back().get_int();
						stack.pop_back();
						const int val1 = stack.back().get_int();
						stack.pop_back();
						stack.push_back(stackvalue(val1 - val2));
						break;
				}
				case opcode::MOD:
				{
						const int val2 = stack.back().get_int();
						stack.pop_back();
						const int val1 = stack.back().get_int();
						stack.pop_back();
						stack.push_back(stackvalue(val1%val2));
						break;
				}

				case opcode::BRLT:
				{
						const int val2 = stack.back().get_int();
						stack.pop_back();
						const int val1 = stack.back().get_int();
						stack.pop_back();
						if (val1 < val2)
						{
								int index = instruction->data.get_int();
								from = ip;
								ip = jumptable[index];
						}
						break;
				}
				case opcode::BRLE:
				{
						const int val2 = stack.back().get_int();
						stack.pop_back();
						const int val1 = stack.back().get_int();
						stack.pop_back();
						if (val1 <= val2)
						{
								int index = instruction->data.get_int();
								from = ip;
								ip = jumptable[index];
						}
						break;
				}
				case opcode::BRFALSE:
				{
						if (!stack.back().get_bool())
						{
								int index = instruction->data.get_int();
								from = ip;
								ip = jumptable[index];
						}
						stack.pop_back();
						break;
				}
				case opcode::BRTRUE:
				{
						if (stack.back().get_bool())
						{
								int index = instruction->data.get_int();
								from = ip;
								ip = jumptable[index];
						}
						stack.pop_back();
						break;
				}
				case opcode::JMP:
				{
						const int index = instruction->data.get_int();
						from = ip;
						ip = jumptable[index];

						break;
				}

				case opcode::CALL:
				{
						stack.pop_back();
						break;

						string function = instruction->data.get_string();
						if (function == "print")
						{
								cout << stack.back().get_string() << endl;
								stack.pop_back();
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
