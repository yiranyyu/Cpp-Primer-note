#include "stdafx.h"
#include <iostream>
#include <iomanip>
#include <string>
void E_2_1()
{
    std::cout << std::setiosflags(std::ios::fixed);
    wchar_t c = L'\x123';
    char32_t c2 = char32_t('\x12');
    int i = 0x123;
    std::cout << c << " " << i
        << std::endl;
 }

void E_2_8()
{
    // using / following three octal digit to represent a character
    // \062 is '2' \011 is '\t' \115 is 'M' \012 is '\n'
    std::cout << "\062\011\115\012" << std::endl;
}