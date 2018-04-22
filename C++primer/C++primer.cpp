
#include "stdafx.h"
//#include <boost/filesystem.hpp>
//#include <boost/type_index.hpp>
#include <iostream>

class B1{public: virtual void print(){std::cout << "B1" << std::endl;}};
class B2{public: virtual void print(){std::cout << "B2" << std::endl;}};
class D1:public B1{};
class D2:public B2{};

class MI:public D1, public D2{};

class MDirect: public B1, public B2{};

class B{public: virtual void print(){std::cout << "B" << std::endl;}};
class D:public B{};

int main()
{
    B1 *pb1 = new MDirect;
    pb1->print();
    MI().print();
    return 0;
}