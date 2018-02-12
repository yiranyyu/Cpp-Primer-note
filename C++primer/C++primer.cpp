
#include "stdafx.h"

#include <iostream>
#include <vector>
#include <string>
using namespace std;

#define LEN 'Z'
char Reverse_of[LEN];
void fill_reverse()
{
    for (int i = 0; i < LEN; ++i)
        Reverse_of[i] = 0;
    Reverse_of['A'] = 'A';
    Reverse_of['E'] = '3';
    Reverse_of['H'] = 'H';
    Reverse_of['I'] = 'I';
    Reverse_of['J'] = 'L';
    Reverse_of['L'] = 'J';
    Reverse_of['M'] = 'M';
    Reverse_of['O'] = 'O';
    Reverse_of['S'] = '2';
    Reverse_of['T'] = 'T';
    Reverse_of['U'] = 'U';
    Reverse_of['V'] = 'V';
    Reverse_of['W'] = 'W';
    Reverse_of['X'] = 'X';
    Reverse_of['Y'] = 'Y';
    Reverse_of['Z'] = '5';
    Reverse_of['1'] = '1';
    Reverse_of['2'] = 'S';
    Reverse_of['3'] = 'E';
    Reverse_of['5'] = 'Z';
    Reverse_of['8'] = '8';
}
bool check_huiwen(string &input)
{
    auto first = input.begin();
    auto last = first + (input.size() - 1);
    while (first < last)
    {
        if (*first != *last)
            return false;
        ++first, --last;
    }
    return true;
}
bool check_jingxiang(string &input)
{
    auto first = input.begin();
    auto last = first + (input.size() - 1);
    char first_value = 0;
    char last_value  = 0;
    while (first <= last)
    {
        first_value = *first;
        last_value = *last;
        if (Reverse_of[first_value] == 0 ||
            Reverse_of[last_value] == 0 ||
            Reverse_of[first_value] != last_value)
            return false;
        ++first, --last;
    }
    return true;
}
int main()
{
    fill_reverse();// init reverse array
    string input;
    while (getline(cin, input))
    {
        if (input.empty())
            break;
        bool isHuiWen = check_huiwen(input);
        bool isJingxiang = check_jingxiang(input);
        cout << input;

        if (isHuiWen)// 回文
        {
            if (isJingxiang)
                cout << " -- is a mirrored palindrome.";
            else
                cout << " -- is a regular palindrome.";
        }
        else         // 不是回文
        {
            if (isJingxiang)
                cout << " -- is a mirrored string.";
            else
                cout << " -- is not a palindrome.";
        }
    }
    auto com = [](int a, int b)->bool {
        return a < b;
    };
    //system("pause");
    return 0;
}