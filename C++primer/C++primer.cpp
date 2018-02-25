
#include "stdafx.h"
#include "Sales_data.h"
#include <iostream>
#include "Blob.h"
//#include <boost/filesystem.hpp>
// #include <boost/type_index.hpp>
#include <fstream>
#include "TextQuery.h"
using namespace std;

void finished();
class C { const int a[3] = { 3, 3, 2 }; public:C() { } };
int main()
{
    C c{}
    ;
    C c2 = c;
    C c3(c2);
    finished();
    return 0;
}

void finished()
{
    cout << endl << "program finished";
    //getchar();
}
