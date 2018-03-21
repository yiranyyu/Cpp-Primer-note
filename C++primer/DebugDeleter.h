#pragma once
#include <iostream>
class DebugDeleter
{
public:
    template <typename T>
    void operator()(T *p)
    {
        std::cout << "deleting" << *p << std::endl;
        delete p;
    }
};

