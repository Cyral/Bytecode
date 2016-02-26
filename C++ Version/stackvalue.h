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
				boolean = value;
		};
		inline stackvalue(const stackvalue &value) {
			dataType = value.dataType;
			if (value.dataType == valuetype::INT)
				integer = value.integer;
			else if (value.dataType == valuetype::BOOL)
				boolean = value.boolean;
			//	else if (value.dataType == valuetype::STR)
			//stackvalue::str = value.str;
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
				return "print";//stackvalue::str;
				// crashes if not explicitly "print" !!!!!!!!!!!
		};
		inline bool get_bool() const {
				if (dataType == valuetype::INT)
						return integer != 0;
				return boolean;
		};
		union {
			int integer;
			//string str;
			bool boolean;
		};
	};
}

#endif
