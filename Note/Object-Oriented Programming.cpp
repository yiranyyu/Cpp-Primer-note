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
}

