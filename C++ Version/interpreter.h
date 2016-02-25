#ifndef BYTECODE_INTERPRETER_H
#define BYTECODE_INTERPRETER_H
#include <vector>
#include <string>
#include <map>
#include "stackvalue.h"
#include "parser.h"
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
		vector<stackvalue*> stack;
		map<int, stackvalue*> locals;
	};
}
#endif
