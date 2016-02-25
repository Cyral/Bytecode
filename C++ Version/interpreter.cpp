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
		for(int ip = 0; ip < num; ip++)
		{
				auto const instruction = &ptr[ip];
				//	cout << ip << endl;
				total++;

				switch (instruction->code)
				{

				case opcode::PUSH:
						stack.push(stackvalue(instruction->data));
						break;

				case opcode::ST:
				{
						locals[instruction->data.get_int()] = stackvalue(stack.pop());
						break;
				}
				case opcode::LD:
				{
						stack.push(stackvalue(locals[instruction->data.get_int()]));
						break;
				}

				case opcode::MUL:
				{
						stack.push(stackvalue(stack.pop().get_int() * stack.pop().get_int()));
						break;
				}

				case opcode::ADD:
				{
						stack.push(stackvalue(stack.pop().get_int() + stack.pop().get_int()));
						break;
				}
				case opcode::SUB:
				{
						const int val2 = stack.pop().get_int();
						const int val1 = stack.pop().get_int();
						stack.push(stackvalue(val1 - val2));
						break;
				}
				case opcode::MOD:
				{
						const int val2 = stack.pop().get_int();
						const int val1 = stack.pop().get_int();
						stack.push(stackvalue(val1%val2));
						break;
				}

				case opcode::BRLT:
				{
						const int val2 = stack.pop().get_int();
						const int val1 = stack.pop().get_int();
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
						const int val2 = stack.pop().get_int();
						const int val1 = stack.pop().get_int();
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
						if (!stack.pop().get_bool())
						{
								int index = instruction->data.get_int();
								from = ip;
								ip = jumptable[index];
						}
						break;
				}
				case opcode::BRTRUE:
				{
						if (stack.pop().get_bool())
						{
								int index = instruction->data.get_int();
								from = ip;
								ip = jumptable[index];
						}
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
						stack.pop();
						break;

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
