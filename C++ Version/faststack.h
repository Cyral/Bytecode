#ifndef BYTECODE_FASTSTACK_H
#define BYTECODE_FASTSTACK_H

#include "stackvalue.h"

using namespace std;

namespace bytecode
{
	struct faststack
	{
  private:
    stackvalue* contents;
    int index;
    int size;
    static const int initialsize = 32;
	public:
    faststack();
   ~faststack();
   inline void push(const stackvalue& value) {
		 contents[++index] = value;
		 // TODO: Implement resizing
	 }
   inline stackvalue pop() {
	   return contents[index--];
	 }
	 inline void mul() {
		 contents[index - 1] = stackvalue(contents[index -1].get_int() * contents[index].get_int());
		 index--;
	 }
	 inline void div() {
		 contents[index - 1] = stackvalue(contents[index -1].get_int() / contents[index].get_int());
		 index--;
	 }
	 inline void mod() {
		 contents[index - 1] = stackvalue(contents[index -1].get_int() % contents[index].get_int());
		 	index--;
	 }
	 inline void add() {
		 contents[index - 1] = stackvalue(contents[index -1].get_int() + contents[index].get_int());
		 index--;
	 }
	 inline void sub() {
		 contents[index - 1] = stackvalue(contents[index -1].get_int() - contents[index].get_int());
		 index--;
	 }
	};
}
#endif
