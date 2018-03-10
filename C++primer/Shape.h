#pragma once
class Shape
{
public:
    Shape();
    Shape(bool _visibility);
    virtual ~Shape() = 0;
    virtual void draw() const = 0;
protected:
    bool visibility = true;
};

