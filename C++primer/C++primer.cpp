
#include "stdafx.h"
//#include <boost/filesystem.hpp>
//#include <boost/type_index.hpp>
#include <iostream>
#include <bitset>
#include <regex>
using namespace std;

int main()
{
    // find the characters ei that follows a character other than c
    string pattern("[^c]ei");

    // we want the whole word in which our pattern appears
    pattern = "([[:alpha:]]*" + pattern + "[[:alpha:]]*)([[:digit:]])*";

    regex r(pattern);       // construct a regex to find pattern
    string fmt2 = "$2#";

    string s = "dfei2 k freigh4";

    // tell regex_replace to copy only the text that it replaces
    cout << regex_replace(s, r, fmt2) << endl;
    getchar();
    return 0;
}