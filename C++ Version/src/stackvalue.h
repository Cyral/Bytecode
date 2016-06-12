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
		inline stackvalue() {
			stackvalue::dataType = valuetype::NONE;
		}
		inline stackvalue(const int value){
				dataType = valuetype::INT;
				integer = value;
		};
		inline stackvalue(const string value){
				dataType = valuetype::STR;
		};
		inline stackvalue(const bool value){
				dataType = valuetype::BOOL;
				integer = value ? 1 : 0;
		};

		valuetype dataType;
		inline int get_int() const {
				return integer;
		};
		inline string get_string() const {
				if (dataType == valuetype::INT)
				{
						std::ostringstream stm;
						stm << integer;
						return stm.str();
				}
				return "print";
		};
		inline bool get_bool() const {
				return integer != 0;
		};
		int integer;
	};
}

#endif
