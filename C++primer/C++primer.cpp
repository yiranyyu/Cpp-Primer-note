
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
#include "templates.h"
#include "Screen.h"
#include "ty_shared_ptr.h"
using namespace std;

int main()
{
    ty_shared_ptr<int> p(new int(33));
    cout << *p << endl;
    getchar();
    return 0;
}