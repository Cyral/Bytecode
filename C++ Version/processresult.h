#ifndef BYTECODE_PROCESSRESULT_H
#define BYTECODE_PROCESSRESULT_H

#include <map>
#include <vector>
#include "instruction.h"
using namespace std;

namespace bytecode
{
	class processresult
	{
	public:
		processresult();
		processresult(vector<instruction*> final_instructions, map<int, int> jumptable);
		map<int, int> jumptable;
		vector<instruction*> instructions;
	};
}
#endif