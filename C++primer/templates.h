#pragma once
#include <functional>
#include <iostream>

template <typename T>
int compare(const T &lhs, const T &rhs)
{
    if (std::less<T>()(lhs, rhs)) return -1;
    if (std::less<T>()(lhs, rhs)) return 1;
    return 0;
}

template <typename T, size_t N>
void print(const T (&a)[N])
{
    for (size_t i = 0; i < N; ++i)
        std::cout << a[i] << " ";
}