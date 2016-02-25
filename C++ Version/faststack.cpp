#include "faststack.h"

namespace bytecode {
faststack::faststack()
{
  faststack::index = 0;
faststack::contents = new stackvalue[faststack::initialsize];
}
faststack::~faststack(){

}
}
