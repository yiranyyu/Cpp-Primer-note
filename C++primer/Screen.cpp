#include "stdafx.h"
#include "Screen.h"


Screen::Screen() = default;

Screen::Screen(pos _height, pos _width)
    :height(_height), width(_width), contents(_height * _width, ' ')
{}

Screen::Screen(pos _height, pos _width, char c)
    :height(_height), width(_width), contents(_height * _width, c)
{}

Screen & Screen::move(pos row, pos col)
{
    ++access_ctr;
    cursor = row * width + col;
    return *this;
}

void Screen::clear()
{
    for (auto &c : contents)
        c = ' ';
}

void Screen::do_display(std::ostream & out) const
{
    out << contents;
}
