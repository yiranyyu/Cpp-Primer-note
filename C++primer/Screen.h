#pragma once
#include <string>
#include <iosfwd>
#include <iostream>

template<size_t width, size_t height>
class Screen
{
public:
    using pos = std::string::size_type;
public:
    Screen();
    Screen(char c);
    
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


template <size_t _width, size_t _height>
Screen<_width, _height>::Screen()
    :height(_height), width(_width), contents(_height * _width, ' ')
{}

template <size_t _width, size_t _height>
Screen<_width, _height>::Screen(char c)
    : height(_height), width(_width), contents(_height * _width, c)
{}

template <size_t width, size_t height>
Screen<width, height>&
Screen<width, height>::move(pos row, pos col)
{
    ++access_ctr;
    cursor = row * width + col;
    return *this;
}

template <size_t width, size_t height>
void Screen<width, height>::clear()
{
    for (auto &c : contents)
        c = ' ';
}

template <size_t width, size_t height>
void Screen<width, height>::do_display(std::ostream & out) const
{
    out << contents;
}

template <size_t width, size_t height>
inline char Screen<width, height>::get() const
{
    ++access_ctr;
    return contents[cursor];
}

template <size_t width, size_t height>
inline char Screen<width, height>::get(pos row, pos col) const
{
    ++access_ctr;
    pos index = row * width + col;
    return contents[index];
}

template <size_t width, size_t height>
inline Screen<width, height>& 
Screen<width, height>::set(char c)
{
    contents[cursor] = c;
    return *this;
}

template <size_t width, size_t height>
inline Screen<width, height>& 
Screen<width, height>::set(pos row, pos col, char c)
{
    pos index = row * width + col;
    contents[index] = c;
    return *this;
}

template <size_t width, size_t height>
inline Screen<width, height>&
Screen<width, height>::display(std::ostream & out)
{
    do_display(out);
    return *this;
}

template <size_t width, size_t height>
inline const Screen<width, height>&
Screen<width, height>::display(std::ostream & out) const
{
    do_display(out);
    return *this;
}

template <size_t width, size_t height>
inline typename Screen<width, height>::pos 
Screen<width, height>::size() const noexcept
{
    return width * height;
}