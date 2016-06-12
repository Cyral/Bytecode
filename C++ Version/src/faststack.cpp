#include "faststack.h"

namespace bytecode {
faststack::faststack()
{
		faststack::index = 0;
		faststack::size = faststack::initialsize;
		faststack::contents = new stackvalue[faststack::initialsize];
}
faststack::~faststack(){
		if (faststack::index != 0)
				delete [] faststack::contents;
}
}
