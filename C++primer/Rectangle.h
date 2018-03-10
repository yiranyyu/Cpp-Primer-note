#pragma once
#include "Shape.h"
class Rectangle :
    public Shape
{
    using MyBase = Shape;
public:
    Rectangle();
    Rectangle(double _width, double _height);
    Rectangle(double _width, double _height, bool _visibility);
    virtual ~Rectangle();
    virtual void draw() const override;
private:
    double width = 0.0;
    double height = 0.0;
};

