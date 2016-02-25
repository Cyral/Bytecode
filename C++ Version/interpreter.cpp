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
		interpreter::locals = map<int, stackvalue*>();
		interpreter::stack = vector<stackvalue*>();
}

void interpreter::run() {
		auto parserResult = interpreter::parser->run(interpreter::lines);
		auto optimizedResult = parserResult;//optimizer.Run(parserResult);
		auto instructions = optimizedResult->instructions;
		auto jumptable = optimizedResult->jumptable;

		int from = 0;
		int total = 0;
		for (int ip = 0; ip < instructions.size(); ip++)
		{
				total++;
				auto const instruction = instructions[ip];

				switch (instruction->code)
				{

				case opcode::PUSH:
						stack.push_back(new stackvalue(*instruction->data));
						break;

				case opcode::ST:
				{
						const int index = instruction->data->get_int();
						delete locals[index];
						auto back = stack.back();
						locals[index] = new stackvalue(*back);
						stack.pop_back();
						delete back;
						break;
				}
				case opcode::LD:
				{
						const int index = instruction->data->get_int();
						stack.push_back(new stackvalue(*locals[index]));
						break;
				}

				case opcode::MUL:
				{
						auto b2 = stack.back();
						int val2 = b2->get_int();
						stack.pop_back();
						delete b2;
						auto b1 = stack.back();
						int val1 = b1->get_int();
						stack.pop_back();
						delete b1;

						stack.push_back(new stackvalue(val1*val2));
						break;
				}

				case opcode::ADD:
				{
					const auto b2 = stack.back();
					const int val2 = b2->get_int();
					stack.pop_back();
					delete b2;
					const auto b1 = stack.back();
					const int val1 = b1->get_int();
					stack.pop_back();
					delete b1;
						stack.push_back(new stackvalue(val1 + val2));
						break;
				}
				case opcode::SUB:
				{
					const auto b2 = stack.back();
					const int val2 = b2->get_int();
					stack.pop_back();
					delete b2;
					const auto b1 = stack.back();
					const int val1 = b1->get_int();
					stack.pop_back();
					delete b1;
						stack.push_back(new stackvalue(val1 - val2));
						break;
				}
				case opcode::MOD:
				{
					const auto b2 = stack.back();
					const int val2 = b2->get_int();
					stack.pop_back();
					delete b2;
					const auto b1 = stack.back();
					const int val1 = b1->get_int();
					stack.pop_back();
					delete b1;

						stack.push_back(new stackvalue(val1%val2));
						break;
				}

				case opcode::BRLT:
				{
					const auto b2 = stack.back();
					const int val2 = b2->get_int();
					stack.pop_back();
					delete b2;
					const auto b1 = stack.back();
					const int val1 = b1->get_int();
					stack.pop_back();
					delete b1;
						if (val1 < val2)
						{
								int index = instruction->data->get_int();
								from = ip;
								ip = jumptable[index] - 1;
						}
						break;
				}
				case opcode::BRLE:
				{
					const auto b2 = stack.back();
					const int val2 = b2->get_int();
					stack.pop_back();
					delete b2;
					const auto b1 = stack.back();
					const int val1 = b1->get_int();
					stack.pop_back();
						if (val1 <= val2)
						{
								int index = instruction->data->get_int();
								from = ip;
								ip = jumptable[index] - 1;
						}
						break;
				}
				case opcode::BRFALSE:
				{
						const auto p = stack.back();
						if (!p->get_bool())
						{
								int index = instruction->data->get_int();
								from = ip;
								ip = jumptable[index] - 1;
						}
						stack.pop_back();
						delete p;
						break;
				}
				case opcode::BRTRUE:
				{
						const auto p = stack.back();
						if (p->get_bool())
						{
								int index = instruction->data->get_int();
								from = ip;
								ip = jumptable[index] - 1;
						}
						stack.pop_back();
						delete p;
						break;
				}
				case opcode::JMP:
				{
						const int index = instruction->data->get_int();
						from = ip;
						ip = jumptable[index] - 1;

						break;
				}

				case opcode::CALL:
				{
						const auto p = stack.back();
						stack.pop_back();
						delete p;
						break;
						string function = instruction->data->get_string();
						if (function == "print")
						{
								cout << stack.back()->get_string() << endl;
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
