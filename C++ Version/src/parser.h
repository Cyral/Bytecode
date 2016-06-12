#ifndef BYTECODE_PARSER_H
#define BYTECODE_PARSER_H
#include <vector>
#include <string>
#include <map>
#include <iostream>
#include <sstream>

#include "processresult.h"
#include "opcode.h"
#include "valuetype.h"
using namespace std;

namespace bytecode
{
	struct parser
	{
	public:
		parser();
		processresult* run(vector<string> lines);
	private:
		opcode get_opcode(string str);
		map<string, opcode> op_map;
		valuetype get_valuetype(string str);
	};
}
#endif