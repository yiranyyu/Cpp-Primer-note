#include "Rectangle.h"
#include <iostream>


Rectangle::Rectangle() = default;

Rectangle::Rectangle(double _width, double _height)
    :width(_width), height(_height)
{}

Rectangle::Rectangle(double _width, double _height, bool _visibility)
    :MyBase(_visibility), width(_width), height(_height)
{}


Rectangle::~Rectangle() = default;

void Rectangle::draw() const
{
    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            putchar('#');
        }
        putchar('\n');
    }
}
