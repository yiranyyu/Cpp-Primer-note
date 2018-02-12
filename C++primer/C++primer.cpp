
#include "stdafx.h"
#include "Sales_data.h"
#include "Person.h"
using namespace std;

int main()
{
    Person p1("Li");
    Person p2("Hi");
    p2 = p1;
    Sales_data sd;
    read(cin, sd);
    system("pause");
    return 0;
}