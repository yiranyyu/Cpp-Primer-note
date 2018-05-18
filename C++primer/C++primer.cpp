
#include "stdafx.h"
//#include <boost/filesystem.hpp>
//#include <boost/type_index.hpp>
#include <iostream>
using namespace std;



class outter
{
public:
    class pub{public: int i; void f();};
private:
    class pri{public: int i;};
protected:
    class pro{public: int i;};
};

int main()
{
    cout << sizeof(string) << endl;
    return 0;
}