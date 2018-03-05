
#include <iostream>
#include <algorithm>
#include <iterator>
#include <fstream>
#include "stdafx.h"
#include "Sales_data.h"
#include "Blob.h"
#include <functional>
//#include <boost/filesystem.hpp>
//#include <boost/type_index.hpp>
#include "TextQuery.h"
#include "BlobPtr.h"
using namespace std;

void finished();

class B {
public:
    virtual void f(){}
};

class D1 : public B {
public:
    virtual int f(){}
};

int main()
{
    D1();
    ifstream in("G:\\Code\\Algorithms note\\testfile\\tale.txt");
    finished();
    return 0;
}

void finished()
{
    cout << endl << "program finished";
    getchar();
}
