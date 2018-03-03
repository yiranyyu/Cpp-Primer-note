
#include <iostream>
#include <fstream>
#include "stdafx.h"
#include "Sales_data.h"
#include "Blob.h"
//#include <boost/filesystem.hpp>
//#include <boost/type_index.hpp>
#include "TextQuery.h"
using namespace std;

void finished();
class T{
public:
    T() { cout << "default" << endl; }
    T(const T &that) { cout << "copy" << endl; }
    T(T &&that) { cout << "move" << endl; }
};

class comp {
public:
    comp(const T &_str, int _id):str(_str), id(_id){}
    T str;
    int id;
};

class TEST {
public:
    void f()const & { cout << "called" << endl; }
};


int main()
{
    const char *str1 = "nihao";
    decltype(str1) str2 = "nihaos";


    cout << (str1 == str2) << endl;
    cout << str1 << " " << str2 << endl;


    comp cp(T(), 1);
    comp cp2(cp);
    comp cp3(std::move(cp));
    cout << cp.id;

    TEST().f();

    ifstream in("G:\\Code\\Algorithms note\\testfile\\tale.txt");
    finished();
    return 0;
}

void finished()
{
    cout << endl << "program finished";
    getchar();
}
