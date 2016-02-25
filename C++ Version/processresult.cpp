#include "processresult.h"
#include "instruction.h"

namespace bytecode {
	processresult::processresult()
	{
		processresult::instructions = vector<instruction*>();
		processresult::jumptable = map<int, int>();
	}
	processresult::processresult(vector<instruction*> final_instructions, map<int, int> jumptable)
	{
		processresult::instructions = final_instructions;
		processresult::jumptable = jumptable;
	}
}
