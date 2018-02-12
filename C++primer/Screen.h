#pragma once
#include <string>
class Screen
{
public:
    using pos = std::string::size_type;
public:
    Screen();
    Screen(pos _height, pos _width, char c);
    
    char get() const
    {
        return contents[cursor];
    }
    
    inline char get(pos row, pos col) const;
    
    Screen& move(pos row, pos col);
private:
    pos cursor = 0;
    pos height = 0;
    pos width = 0;
    std::string contents;
};

