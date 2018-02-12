#include "stdafx.h"
#include "Screen.h"


Screen::Screen() = default;



Screen::Screen(pos _height, pos _width, char c)
    :height(_height), width(_width), contents(_height * _width, c)
{}

inline char Screen::get(pos row, pos col) const
{
    pos index = row * width + col;
    return contents[index];
}

Screen & Screen::move(pos row, pos col)
{
    cursor = row * width + col;
    return *this;
}
