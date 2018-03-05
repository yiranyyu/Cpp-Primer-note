#include <functional>
#include <map>
using namespace std;
namespace note{int OverloadedOperationsAndConversions(){

// 1. 2. 3. have same call signature int(int, int), i.e. same function type.
// so we can easily use std::map<std::string, function<int(int, int)>> to organize them.
    auto mod = [](int i, int j) { return i % j; };      // 1.
    int add(int i, int j); /*{ return i + j; }*/        // 2.
    struct divide{                                      // 3. 
        int operator()(int denominator, int divisor){
            return denominator / divisor;
        }
    };

    using func_type = function<int(int, int)>;
    func_type f1(add);
    func_type f2(mod);
    func_type f3 = divide();

    map<string, func_type> table;
    table["+"] = f1;
    table["%%"]= f2;
    table["/"] = f3;   
    table["-"] = minus<int>();
}
}