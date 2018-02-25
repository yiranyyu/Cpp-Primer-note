#include <string>
namespace note{ void DynamicMemory(){

auto pi = new int();// type of pi : int *
auto pCstr = new auto("string"); // type of pCstr : const char **
auto pStr = new auto(std::string("string"));// type of pStr : const std::string *

// allocate const obj
const int *cpi = new const int(); // like normal, must init


// Memory Exhaustion
int *p1 = new int; // if allocation fail, new throws std::bad_alloc
int *p2 = new (std::nothrow) int;// if allocation fail, return null pointer
}}