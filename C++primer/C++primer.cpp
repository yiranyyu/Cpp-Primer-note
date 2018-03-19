
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
//#include <boost\filesystem.hpp>
#include <map>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include "DiscountQuote.h"
#include "BulkQuote.h"
#include "BinaryQuery.h"
#define max(lhs, rhs) (lhs > rhs ? lhs : rhs)
using namespace std;
void finished();

int main()
{
    while (true)
    {
        int buf[8];
        cout << "input: " << endl;
        for (int i = 0; i <= 8; ++i)
            fscanf_s(stdin, "%d", buf + i);
        for (auto i : buf)
            cout << i << endl;
    }
    //Query query = Query("the") & Query("not") & ~Query("a") & ~Query("of") & ~Query("to");
    //ifstream file("G:\\Code\\Algorithms note\\testfile\\tale.txt");
    //cout << query.evaluate(TextQuery(file)) << endl;
    finished();
    return 0;
}

void finished()
{
    cout << endl << "program finished";
    system("pause");
    getchar();
}
