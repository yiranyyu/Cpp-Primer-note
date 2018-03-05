namespace note{void ObjectOrientedProgramming(){

class Base
{
public:
    virtual Base* rtnPtr() { return 0; }
};

class Derived : public Base
{
public:
    virtual Derived* rtnPtr() override{ return 0; } // ok , Derived is derived-class of Base.
};
}}

