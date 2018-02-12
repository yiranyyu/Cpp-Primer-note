#include "stdafx.h"
#include <iostream>
#include <algorithm>
#include <iomanip>
#include <vector>
#include "Tools.h"
#include "Sales_item.h"
#include <set>
void E_1_3()
{
    std::cout << "Hello World" << std::endl;
}

void E_1_4()
{
    std::cout << "Enter two numbers:" << std::endl;
    int a = 0;
    int b = 0;
    std::cin >> a >> b;
    std::cout << "The product of " << a << " and " << b
        << " is " << (a * b) << std::endl;
}

void E_1_5()
{
    std::cout << "Enter two numbers:";
    std::cout << std::endl;
    int v1 = 0;
    int v2 = 0;
    std::cin >> v1 >> v2;
    std::cout << "The sum of ";
    std::cout << v1;
    std::cout << " and ";
    std::cout << v2;
    std::cout << " is ";
    std::cout << v1 + v2;
    std::cout << std::endl;
}

void E_1_8()
{
    std::cout << "/*";
    std::cout << "*/";
    //std::cout << /* "*/" */;// test the sytax of comment pairs, this statement is wrong
    std::cout << /*  "*/" /*  "/*"  */; // complicated comment pairs( not recomended)
}

void E_1_9()
{
    int start = 50; // start of numbers(inclusive)
    int cur = start;
    int end = 100;  // end of numbers(inclusive)
    int amount = 0;
    while (cur <= end)
        amount += cur++;
    // print the result
    std::cout << "sum of " << start << " to "
        << end << " is " << amount << std::endl;
}

void E_1_10()
{
    int start = 10; //start of numbers(inclusive)
    int cur = start;
    int end = 0;    // end of numbers(inclusive)
    int amount = 0;
    while (cur >= end)
        amount += cur--;
    // print the result
    std::cout << "sum of " << start << " to "
        << end << " is " << amount << std::endl;
}

void E_1_11()
{
    std::cout << "Enter two integers:" << std::endl;
    int min = 0;// start of numbers to print.(inclusive)
    int max = 0;// end of numbers to print.(inclusive)

                // read in numbers and check range
    std::cin >> min >> max;
    min = Tools::min(min, max);
    max = Tools::max(min, max);

    int cur = min;
    int i = 1;// help to config the output syntax
    while (cur <= max)
    {
        std::cout << std::setw(8) << cur++;
        if (i++ % 8 == 0)
            std::cout << std::endl;
    }
}

void E_1_12()
{
    // this loop sum up numbers from -100 to 100
    int sum = 0;
    for (int i = -100; i <= 100; ++i)
        sum += i;
    std::cout << sum << std::endl;
}

void E_1_13()
{
    // using for (int cur = start; cur <= end; ++cur) format.
}

void E_1_16()
{
    long sum = 0;
    int input = 0;
    while (std::cin >> input)
        sum += input;
    std::cout << "sum is " << sum << std::endl;
}

void E_1_17()
{
    int curVal = 0;
    int inputVal = 0;
    if (std::cin >> curVal)
    {
        int cnt = 1;// count of same numbers
        while (std::cin >> inputVal)
        {
            if (inputVal == curVal)
                ++cnt;
            else
            {
                std::cout << curVal << " occurs " << cnt << " times." << std::endl;
                curVal = inputVal;
                cnt = 1;
            }
        }
        std::cout << curVal << " occurs " << cnt << " times." << std::endl;
    }
}

void E_1_20()
{
    Sales_item item;
    std::vector<Sales_item> items;
    while (std::cin >> item)
    {
        items.push_back(item);
    }
    for (auto cur = items.begin();
        cur != items.end();
        ++cur)
        std::cout << *cur << std::endl;
}

void E_1_21()
{
    Sales_item item_1;
    Sales_item item_2;
    std::cin >> item_1;
    std::cin >> item_2;
    std::cout << (item_1 + item_2) << std::endl;
}

void E_1_22()
{
    Sales_item input_item;
    Sales_item sum;
    std::cin >> sum;
    while (std::cin >> input_item)
        sum += input_item;
    std::cout << sum << std::endl;
}

void E_1_23()
{
    // use specialized less template to sort the items with its order of ISBN
    std::multiset<Sales_item, compare_Sales_item_with_ISBN> items;

    Sales_item item;
    while (std::cin >> item)
        items.insert(item);

    if (items.size() == 0)
        return;

    auto cur = items.begin();
    auto end = items.end();
    std::string last_ISBN = cur->isbn();
    std::string cur_ISBN;
    ++cur;
    long cnt = 1;// number of transactions of same ISBN

    for (; cur != end; ++cur)
    {
        cur_ISBN = cur->isbn();
        if (cur_ISBN == last_ISBN)
            ++cnt;
        else
        {
            std::cout << last_ISBN << " occurs " << cnt
                << " times " << std::endl;
            cnt = 1;
            last_ISBN = cur_ISBN;
        }
    }
    std::cout << cur_ISBN << " occurs " << cnt << " items " << std::endl;
}

// read records from standard input
void E_1_24()
{
    Sales_item cur_item;
    std::vector<Sales_item> items;
    while (std::cin >> cur_item)
    {
        items.push_back(cur_item);
    }
    std::sort(items.begin(), items.end(), compare_Sales_item_with_ISBN());
    
    size_t length = items.size();

    Sales_item item;    // sum of Sales_item with different ISBN
    auto cur = items.begin();
    item = *cur;
    ++cur;
    auto end = items.end();
    while (cur != end)
    {
        cur_item = *cur;
        if (item.same_ISBN_with(cur_item))
        {
            item += cur_item;// calculate sum
        }
        else
        {
            std::cout << item << std::endl;// output sum of Sales_item with certain ISBN
            item = cur_item;
        }
    }
    std::cout << item << std::endl;// output the last item 
}