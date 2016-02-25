#ifndef BYTECODE_STACKVALUE_H
#define BYTECODE_STACKVALUE_H
#include <string>
#include <sstream>
#include "valuetype.h"
using namespace std;

namespace bytecode
{
	struct stackvalue {
	public:
		stackvalue() {
			stackvalue::dataType = valuetype::NONE;
		}
		stackvalue(string);
		stackvalue(int);
		stackvalue(bool);
		stackvalue(const stackvalue &value);
		~stackvalue();
		valuetype dataType;
		string get_string() const;
	  int get_int() const;
		bool get_bool() const;
		union {
			int integer;
			//string str;
			bool boolean;
		};
	};
}

#endif
