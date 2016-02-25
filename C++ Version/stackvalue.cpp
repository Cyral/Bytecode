#include "stackvalue.h"
#include <iostream>
namespace bytecode {


stackvalue::stackvalue(const stackvalue &value)
{
		stackvalue::dataType = value.dataType;
		if (value.dataType == valuetype::INT)
				stackvalue::integer = value.integer;
		else if (value.dataType == valuetype::BOOL)
				stackvalue::boolean = value.boolean;
		//	else if (value.dataType == valuetype::STR)
		//stackvalue::str = value.str;
}
stackvalue::stackvalue(string const value) {
		//	stackvalue::str = value;
		stackvalue::dataType = valuetype::STR;
}

stackvalue::stackvalue(int const value) {
		stackvalue::integer = value;
		stackvalue::dataType = valuetype::INT;
}
stackvalue::stackvalue(bool const value) {
		stackvalue::boolean = value;
		stackvalue::dataType = valuetype::BOOL;
}
stackvalue::~stackvalue() {

}
int stackvalue::get_int()  const {
		return stackvalue::integer;
}
string stackvalue::get_string()  const {
		if (stackvalue::dataType == valuetype::INT)
		{
				std::ostringstream stm;
				stm << stackvalue::integer;
				return stm.str();
		}
		return "print";//stackvalue::str;
		// crashes if not explicitly "print" !!!!!!!!!!!
}
bool stackvalue::get_bool()  const {
		if (stackvalue::dataType == valuetype::INT)
				return stackvalue::integer != 0;
		return stackvalue::boolean;
}
}
