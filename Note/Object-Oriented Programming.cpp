namespace note{

class Base
{
public:
    virtual Base* rtnPtr() { return 0; }
protected:
    int prot_mem;
};

class Derived : public Base
{
    friend class Pal;
public:
    virtual Derived* rtnPtr() override{ return 0; } // ok , Derived is derived-class of Base.
};


// Derived class has no special access to the protected members of base-class objects.
class Sneaky : public Base
{
    friend void clobber(Sneaky&);
    friend void clobber(Base&);

    int j; // private by default;
};

// ok: clobber can access the private and protected members of Sneaky objects.
void clobber(Sneaky &s) { s.j = s.prot_mem = 0;}

// error: clobber can't access the protected members in Base;
void clobber(Base &b) {/*    b.prot_mem = 0; */}

class Pal
{
    int f(Base b){return b.prot_mem;} // ok: pal is a friend of Base

    int f2(Sneaky s) { return s.j; } // error: Pal is not friend of Sneaky

    int f3(Sneaky s) { return s.prot_mem ;}// ok: Pal is a friend of Base
};


class PriDerived : private Base
{
public:
    using Base::rtnPtr; // maintain access level for public member of base class
protected:
    using Base::prot_mem;
};

class Constructor
{
public:
    Constructor(int i, int j = 3) :v1(i), v2(j){}
    int v1, v2;
};

class InheritConstructor : public Constructor 
{
    using Constructor::Constructor;

    /*
    get two ctors like:

    InheritConstructor(int i) :Construtor(i){}

    InheritConstructor(int i, int j) : Constructor(i, j){}

    not inherit the default value
    */

};
}

