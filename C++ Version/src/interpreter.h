#ifndef BYTECODE_INTERPRETER_H
#define BYTECODE_INTERPRETER_H
#include <vector>
#include <string>
#include <map>
#include "stackvalue.h"
#include "parser.h"
#include "faststack.h"
using namespace std;

namespace bytecode
{
	class interpreter
	{
	public:
		interpreter(vector<string> lines);
		void run();
	private:
		parser* parser;
		vector<string> lines;
		faststack stack;
		map<int, stackvalue> locals;
	};
}
#endif
