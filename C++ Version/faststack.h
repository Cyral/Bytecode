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
	};
}
#endif
