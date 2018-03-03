
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

class T {
    static int ID;
public:
    T() :id(ID++) { cout << "construct " << id << endl; }
    T(const T &that) : id(ID++) { cout << "copy from " << that.id << " to construct " << id << endl; }
    ~T() { cout << "destruct " << id << endl; }
private:
    int id;
};

int T::ID = 1;

int main()
{
    negate<int> n;
    plus<int> add;
    logical_and<int> and;
    less<string*> lst;

    lst(new string, new string);

    vector<string*> pointers;
    for (int i = 0; i < 10; ++i)
        pointers.push_back(new string(i, 's'));
    
    sort(pointers.begin(), pointers.end(), [](auto *ptr, auto *ptr2) {return ptr < ptr2; });

    auto sum = n(add(1, 2));
    cout << sum << endl;
    {
        T t1;
        cout << "ctor lambda" << endl;
        auto lam = [=] {auto c = t1; };

        cout << "call" << endl;
        lam();
    }

    ifstream in("G:\\Code\\Algorithms note\\testfile\\tale.txt");
    finished();
    return 0;
}

void finished()
{
<<<<<<< HEAD
    cout << endl << "program finished";
=======
    cout << endl;
    getchar();
>>>>>>> dev
    getchar();
}
