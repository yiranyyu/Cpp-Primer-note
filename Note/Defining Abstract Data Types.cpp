#include "../C++primer/Sales_data.h"
#include <iostream>
using namespace std;
void note(){
Sales_data item("item");
// explicit keyword

// ok: explicitly force a conversion
item.combine(static_cast<Sales_data>(cin));// call corresponding ctor to do convert
}

// static data member
class Widget_7{
private:
    const static char BACKGROUND = ' ';
public:
    void foo(char = BACKGROUND){}
    // void foo(char = background){} Error, cannot use nonstatic data member as defaull param
private:
    char background;    
};
