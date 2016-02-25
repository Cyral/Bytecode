#include "parser.h"
#include "opcode.h"
#include "processresult.h"
#include "valuetype.h"
#include "instruction.h"
#include "stackvalue.h"
#include "util.h"

using namespace std;

namespace bytecode {
	parser::parser() {
		parser::op_map = map<string, opcode>({
			{ "nop", opcode::NOP},
			{ "push", opcode::PUSH},
			{ "st", opcode::ST},
			{ "ld", opcode::LD},
			{ "mul", opcode::MUL },
			{ "div", opcode::DIV },
			{ "add", opcode::ADD },
			{ "sub", opcode::SUB },
			{ "mod", opcode::MOD },
			{ "eq", opcode::EQ },
			{ "neq", opcode::NEQ },
			{ "jmp", opcode::JMP },
			{ "brfalse", opcode::BRFALSE },
			{ "brtrue", opcode::BRTRUE },
			{ "brlt", opcode::BRLT },
			{ "brle", opcode::BRLE },
			{ "comp", opcode::COMP },
			{ "call", opcode::CALL },
			{ "ret", opcode::RET},
			{ "set", opcode::SET},
		});
	}
	processresult* parser::run(vector<string> lines) {
		auto result = new processresult();

		// Map of labels to the line they correspond with.
		auto tempjumps = map<int, int>();
		for (auto i = 0; i < lines.size(); i++)
		{
			auto line = util::trim(lines[i]);
			int colonIndex = line.find(':', 0);

			// Check for a label (Ex: 2: push.str)
			if (colonIndex > 0 && colonIndex < line.find(' ', 0))
			{
				int index = 0;
				stringstream(line.substr(0, colonIndex)) >> index;
				tempjumps[index] = i;
				line = line.substr(colonIndex + 2);
			}
			lines[i] = line;
		}

		// After parsing labels, parse each bytecode line.
		for (auto i = 0; i < lines.size(); i++)
		{
			string line = lines[i];
			int spaceIndex = line.find(' ', 0);
			// Instruction opcode name
			string instrText = line.substr(0, spaceIndex);
			// Data/arguments
			string dataText = line;
			if (spaceIndex > 0)
				dataText = line.substr(spaceIndex + 1);

			valuetype type = valuetype::NONE;
			int dotIndex = line.find('.', 1);
			// Check for type specifier. (Ex: push.int, push.bool)
			if (dotIndex > 0 && dotIndex < spaceIndex)
			{
				string typeText = line.substr(dotIndex + 1, spaceIndex - dotIndex - 1);
				type = parser::get_valuetype(typeText);
				instrText = line.substr(0, dotIndex);
			}
			opcode code = get_opcode(instrText);
			// Set the type to INT for all types that only accept ints.
			if (code == opcode::LD || code == opcode::ST || code == opcode::JMP || code == opcode::BRFALSE
				|| code == opcode::BRTRUE || code == opcode::BRLE || code == opcode::BRLT)
				type = valuetype::INT;
			else if (code == opcode::CALL)
				type = valuetype::STR;

			stackvalue idata;
			if (type == valuetype::STR)
				idata = stackvalue("print");
			else if (type == valuetype::BOOL)
				idata = stackvalue(dataText != "false");
			else if (type == valuetype::INT)
			{
				int num = 0;
				stringstream(dataText) >> num;
				idata = stackvalue(num);
				// For instructions involving jumps
				if (code == opcode::JMP || code == opcode::BRFALSE || code == opcode::BRTRUE || code == opcode::BRLE || code == opcode::BRLT)
					result->jumptable[num] = tempjumps[num];
			}
			result->instructions.push_back(new instruction(code, type, idata));
		}

		return result;
	}

	opcode parser::get_opcode(string str)
	{
		return parser::op_map[str];
	}
	valuetype parser::get_valuetype(string str)
	{
		if (str == "int")
			return valuetype::INT;
		if (str == "str")
			return valuetype::STR;
		if (str == "bool")
			return valuetype::BOOL;
		cout << "Invalid type: " << str << endl;
	}
}
