#pragma once
#include <string>
#include <iosfwd>
class Screen
{
public:
    using pos = std::string::size_type;
public:
    Screen();
    Screen(pos _height, pos _width);
    Screen(pos _height, pos _width, char c);
    
    char get() const;
    char get(pos row, pos col) const;

    Screen& set(char c);
    Screen& set(pos row, pos col, char c);
    
    Screen& display(std::ostream &out = std::cout);
    const Screen& display(std::ostream &out = std::cout) const;

    Screen& move(pos row, pos col);

    void clear();
     
    pos size() const noexcept;
private:
    pos cursor = 0;
    pos height = 0;
    pos width = 0;
    std::string contents;
    mutable size_t access_ctr = 0U;
private:
    void do_display(std::ostream& out)const;
};

inline char Screen::get() const
{
    ++access_ctr;
    return contents[cursor];
}

inline char Screen::get(pos row, pos col) const
{
    ++access_ctr;
    pos index = row * width + col;
    return contents[index];
}

inline Screen& Screen::set(char c)
{
    contents[cursor] = c;
    return *this;
}

inline Screen& Screen::set(pos row, pos col, char c)
{
    pos index = row * width + col;
    contents[index] = c;
    return *this;
}

inline Screen & Screen::display(std::ostream & out)
{
    do_display(out);
    return *this;
}

inline const Screen & Screen::display(std::ostream & out) const
{
    do_display(out);
    return *this;
}

inline Screen::pos Screen::size() const noexcept
{
    return width * height;
}