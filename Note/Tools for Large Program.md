# Tools for Large Program

## Exception Handling

**Exception handling** allows independently developed parts of a program to communicate about and handle problems that arise at run time.

### Throwing an Exception

#### Stack Unwinding

When an exception is thrown, execution of the current functions is suspended and the search for a matching `catch` clause begins. The process, known as **stack unwinding**, continues up the chain of nested function calls until a `catch` clause for the exception is found, or the `main` function itself is exited without having found a matching `catch`
Assuming a matching `catch` is found, that `catch` is entered, and the program continues by executing the code inside that `catch`. When the `catch` completes, execution continues at the point immediately after the last `catch` clause associated with that `try` block.
If no matching `catch` is found, the program calls the library **`terminate`** function

#### Objects Are Automatically Destroyed during Stack Unwinding

When a block is exited during stack unwinding, the complier guarantees that objects created in that block are properly destroy. If a local object is of class type, the dtor for that object is called automatically.

#### The Exception Ojbect

The compiler uses the thrown expression to copy initialize a special object known as the **exception object**.
When we throw an expression, the **static**, complie-time type of that expression determine the type of the exception object.

### Catching an Exception

Ordinarily, a `catch` that takes an exception of a type realted by inheritance ought to define its parameter as a reference.

#### Finding a Matching Handler

The rules for when an exception matches a `catch` exception declaration are much more restrictive than the rules used for matching arguments with parameter types. Most conversions are not allowed--the types of the exception and the `catch` declaration must match exactly with only a few possible difference:

* Conversions from non`const` to `const` are allowed
* Conversions from derived type to base type are allowed
* An array is converted to a pointer to the type of the array; a function is converted to the appropriate pointer to function type.

#### Rethrow

A `catch` passes its exception out to another `catch` by **rethrowing** the exception. A rethrow is a `throw` that is not followed by an exception:

```C++
throw;
```

An empty `throw` can appear only in a `catch` or in a function called (directly or indirectly) from a `catch`. If an empty `throw` is encountered when an handler is not active, `terminate` is called

In general, a `catch` might change the contents of its paramter. If, after changing its parameter, the `catch` rethrows the exception, then those changes will be propagated only if the `catch`'s exception declaration is a reference:

```C++
catch (my_error &e)     // catch by reference
{
    e.status = errorCode::severeError;
    throw;      // the status member of the exception object is changed
}
catch(other_error e)    // catch by vlaue
{
    e.status = errorCode::badError;
    throw;      // the status member of the exception object is unchanged
}
```

#### The Catch-All Handler

```C++
try
{
    // actions that may cause an exception to be thrown
}
catch(...)  // catch all exception
{
    // handle the exception
    throw;  // always rethrow it for other process
}
```

### Function `try` Blocks and Constructors

To handle an exception from a ctor initializer, we must write the ctor as a **function `try` block**. A function `try` block lets us associate a group of `catch` clauses with the initialzation phase of a ctor's (of dtor's) function body.

```C++
template <typename T>
Blob<T>::Blob(std::initializer_list<T> il)
try
    : data(std::make_shared<std::vector<T>>(il))
{
    // empty body
}catch(const std::bad_alloc &e)
{
    handle_out_of_memory(e);
}
```

The `catch` associated with this `try` can be used to handle exceptions thrown either from within the memeber initialization list or from within the ctor body.

### The `noexcept` Exception Specification

A function can specify that it does not throw exceptions by providing a **noexcept specification**.

```C++
void recoup(int) noexcept;      // won't thrown
void alloc();                   // might thrown
```

These declarations say that `recoup` will not throw any exceptions and that `alloc` might. We say that `recoup` has a **nonthrowing specification**.

* The `noexcept` specifier must appear on **all of** the declarations and the corresponding definition of a function or on none of them. The specifier precedes a trailing return.
* We may also specify `noexcept` on the declaration and definition of a function pointer.
* It may **not** appear in a `typedef` or type alias.
* In a member function the `noexcept` specifier follows any `const` or reference qualifiers, and it precedes `final`, `override`, or `= 0` on a virtual function.

#### Violating the Exception Specification

It is important to understand that the compiler does not check the `noexcept` specification at compile time.

If a `noexcept` function does throw, `terminate` is called, thereby enforceing the promise not to throw at run time.

As a result, `noexcept` should be used in two cases:

* if we are confident that the function won't throw
* we don't know what we'd do to handle the error anyway.

#### Arguments to the `noexcept` Specification

The `noexcept` specifier takes an optional argument that must be convertible to a `bool`: If the argument is `true`, then the function won't throw; if the argument is `false`, then the function might throw:

```C++
void recoup(int) noexcept(true);        // recoup won't throw
void alloc(int)  noexcept(false);       // alloc can throw
```

#### The `noexcept` Operator

Arguments to the `noexcept` specifier are often composed using the **noexcept operator**. The `noexcept` operator is a unary operator that returns a `bool` rvalue constant expression that indicate whether a given expression might throw. Like `sizeof`, `noexcept` does not evaluate its operand

```C++
noexcept(recoup(i));        // true if calling recoup can't throw, false otherwise
```

We can use the `noexcept` operator to form an exception specifier as follows:

```C++
void f() noexcept(noexcept(g()));   // f has same exception specifer as g
```

#### Exception Specifications and Pointers, Virtuals, and Copy Control

A pointer to function and the function to which that pointer points must have compatible specification.

```C++
// both recoup and pf1 promise not to throw
void (*pf1)(int) noexcept = recoup;

// ok: recoup won't throw; it doesn't matter that pf2 might
void (*pf2)(int) = recoup

pf1 = alloc;    // error: alloc might throw but pf1 said it won't
pf2 = alloc;    // ok: both pf2 and alloc might throw
```

If a virtual function includes a promise not to throw, the inherited virtuals must also promise not to throw. On the other hand, if the base allows exception, it is okay for the derived functions to be more restrictive and promise not to throw:

```C++
class Base
{
public:
    virtual double f1(double)   noexcept;       // doesn't throw
    virtual int f2()            noexcept(false);// can throw
    virtual void f3();                          // can throw
};

class Derived : public Base
{
public:
    double f1(double);              // error Base::f1 promise not to throw
    int f2() noexcept(false);       // ok: same specification as Base::f2
    void f3() noexcept;             // ok: Derived f3 is more restrict
}
```

When the compiler synthesizes the copy-control members, it generates an exception specification for the synthesized member. If all the corresponding operation for all the members and base classes promise not to throw, then the synthesized member is `noexcept`
Moreover, if we do not provide an exception specification for a dtor that we do define, the compiler synthesizes one for us. The compiler generates the same specification as it wound have generated had it synthesized the dtor for that class.

## Namespaces

**Namespaces** provides a much more controlled mechanism for preventing name collisions. Namespaces partitions the global namespace. A namespace is a scope.

### Namespace Definitions

Any declaration that can appear at global scope can be put into a namespace

```C++
namespace cpluscplus_primer
{
    class Sales_data { /* ... */ };
    Sales_data operator+(const Sales_data&,
                         const Sales_data&);
    class Query { /* ... */ };
    class Query_base { /* ... */ };
} // like blocks, namespaces do not end with a semicolon
```

As with any name, a namespace name must be unique within the scope in which the namesapce is defined. Namespaces may be defined at global scope or inside another namespace. They may not be defined inside a function or class.

#### Namespaces Can Be Discontiguous

Writing a namespace definition:

```C++
namespace nsp
{
    // declarations
}
```

either defines a new namespace named `nsp` or adds to an existing one.

* Namespace members that define classes, and declarations for the functions and objects that are part of the class interface, can be put into head files. These headers can be included by files that use those namespace members
* The definition of namespace members can be put in separate source files.

#### Defining Namespace Members

It is also possible to define a namespace member outside its namespace definition. The namespace declaration of name must be in scope, and the definition must specify the namespace to which the name belongs:

```C++
// namespace members defined outside the namespace must use qualified names
cplusplus_primer::Sales_data
cplusplus_primer::operator+(const Sales_data &lhs,
                            const Sales_data &rhs)
{
    Sales_data ret(lhs);
    // ...
}
```

As with class members defined outside a class, once the fully qualified name is seen, we are in the scope of the namespace. Inside the `cplusplus_primer` namespace, we can use other namespace member names without qualification.

Although a namespace memmber can be defined outside its namespace, such definition must appear in an enclosing namespace. That is, we can define the `Sales_data operator+` inside the `cplusplus_primer` namespace or at global scope. We cannot define this operator in an unrelated namespace.

#### Template Specializations

As with any other namespace name, so long as we have declared the specialization inside the namespace, we can define it outside the namespace:

```C++
// we must declare the specialization as a member of stds
namespace std {
    template <> struct hash<Sales_data>;
}

// having added the declaration for the specialization to `std`
// we can define the specialization outside the std namespace
template <>
struct std::hash<Sales_data>
{
    size_t operator()(const Sales_data &s)const
    {
        return hash<string>()(s.bookNo) ^
               hash<unsigned>()(s.units_sold) ^
               hash<double>()(s.revenue);
    }
    // other members ...
}
```

#### The Global Namespace

Names defines at global scope are defined inside the **global namespace**. The global namespace is implicitly declared and exists in every program. Each file that defines entities at global scope (implicitly) adds those names to the global namespace.

The scope operator can be used to refer to members of the global namespace. Because the global namespace is implicit, it does not have a name; the notation

> `::member_name`

refers to a member of the global namespace.

#### Nested Namespaces

A nested namespace is a namespace defined inside another namespace:

```C++
namespace cplusplus_primer {
    // first nested namespace: defines the Query portion of the library
    namespace QueryLib {
        class Query { /* ... */ };
        Query operator&(const Query&, const Query&);
        // ...
    }
    // second nested namespace: defines the Sales_data portion of the library
    namespace Bookstore {
        class Quote { /* ... */ };
        class Disc_quote : public Quote { /* ... */ };
        // ...
    }
}
```

The `cplusplus_primer` namespace now contains two nested namespaces: the namespaces named `QueryLib` and `Bookstore`.

#### Inline Namespaces

The new standard introduced a new kind of nested namespace, an inline namespace. Unlike ordinary nested namespaces, names in an inline namespace can be used as if they were direct members of the enclosing namespace. That is, we need not qualify names from an inline namespace by their namespace name. We can access them using only the name of the enclosing namespace. An inline namespace is defined by preceding the keyword namespace with the keyword inline:

```C++
inline namespace FifthEd {
    // namespace for the code from the Primer Fifth Edition
}
namespace FifthEd { // implicitly inline
    class Query_base { /* ... * /};
    // other Query-related declarations
}
```

The keyword must appear on the first definition of the namespace. If the namespace is later reopened, the keyword inline need not be, but may be, repeated.

Inline namespaces are often used when code changes from one release of an application to the next. For example, we can put all the code from the current edition of the Primer into an inline namespace. Code for previous versions would be in noninlined namespaces:

```C++
namespace FourthEd {
    class Item_base { /* ... */};
    class Query_base { /* ... */};
    // other code from the Fourth Edition
}
```

The overall `cplusplus_primer` namespace would include the definitions of both namespaces. For example, assuming that each namespace was defined in a header with the corresponding name, we'd define cplusplus_primer as follows:

```C++
namespace cplusplus_primer {
    #include "FifthEd.h"
    #include "FourthEd.h"
}
```

Because FifthEd is inline, code that refers to `cplusplus_primer::` will get the version from that namespace. If we want the earlier edition code, we can access it as we would any other nested namespace, by using the names of all the enclosing namespaces: for example, `cplusplus_primer::FourthEd::Query_base`.

#### Unnamed Namespaces

An **unnamed namespace** is the keyword namespace followed immediately by a block of declarations delimited by curly braces. Variables defined in an unnamed namespace have static lifetime: They are created before their first use and destroyed when the program ends.

Unlike other namespaces, an unnamed namespace is local to a particular file and never spans multiple files.

Names defined in an unnamed namespace are used directly; It is not possible to use the scope operator to refer to members of unnamed namespaces.

Names defined in an unnamed namespace are in the same scope as the scope at which the namespace is defined. If an unnamed namespace is defined at the outermost scope in the file, then names in the unnamed namespace must differ from names defined at global scope:

```C++
int i;      // global declaration for i
namespace
{
    int i;
}

// ambiguous: defined globally and in an unnested, unnamed namespace
i = 10;
```

```C++
namespace local
{
    namespace
    {
        int i;
    }
}

// ok: i defined in a nested unnamed namespace is distinct from global i
local::i = 42;
```

* Unnamed Namespaces Replace File Statics
  + Prior to the introduction of namespaces, programs declared names as `static` to make them local to a file. The use of file `static`s is inherited from C.
  + The use of file static declarations is *deprecated* by the C++ standard. File statics should be avoided and *unnamed namespaces* used instead.

### Using Namespace Members

#### Namespace Aliases

A long namespace name such as:

```C++
namespace cplusplus_primer  { /* ... */ }
```

can be associated with a shorter synonym as follow:

```C++
namespace primer = cplusplus_primer;

// or a namespace alias to a nested namespace:
namespace Qlib = cplusplus_primer::QueryLib;

// use the alias:
Qlib::Query q;
```

A namespace can have many synonyms, or alias. All the aliases and the original namespace name can be used interchangeably.

#### `using` Declaration: A Recap

A **`using` declaration** introduces only one namespace member at a time. It allows us to be very specific regarding which names are used in our programs

#### `using` Directives

```C++
using namespace std;
```

A `using` directive may appear in global, local, or namespace scope. It may **not** appear in a class scope.

* `using` Directives and Scope

The scope of names introduced by a using directive is more complicated than the scope of names in using declarations. A using declaration puts the name in the same scope as that of the using declaration itself. It is as if the using declaration declares a local alias for the namespace member.

A `using` directive does not declare local alias. It has the effect of lifting the namespace members into the nearest scope that contains both the namespace itself and the `using` directive.

A `using` directive makes the entire contents of a namespace available In general, a namespace might include definitions that cannot appear in a local scope. As a consequence, **a using directive is treated as if it appeared in the nearest enclosing namespace scope**

```C++
namespace A
{
    int i, j;
}

void f()
{
    using namespace A;      // injects the names from A into the global scope
    cout << i * j << endl;  // uses i and j from namespace A
    // ...
}
```

#### `using` Directives Example

```C++
namespace blip
{
    int i = 16;
    int j = 15;
    int k = 23;
    // other declarations
}

int j = 0;          // ok: j inside blip is hidden inside a namespace

void manip()
{
    // using directive; the names in blip are ''added'' to the global scope
    using namespace blip;   // clash between ::j and blip::j
                            // detected only if j is used

    ++i;            // sets blip::i to 17
    ++j;            // ERROR ambiguous: global j or blip::j?
    ++::j;          // ok: sets global j to 1
    ++blip::j;      // ok: sets blip::j to 16

    int k = 97;     // local k hides blip::k
    ++k;            // sets local k to 98
}
```

The members of `blip` appear as if they were defined in the scope in which both `blip` and manip are defined. Assuming manip is defined at global scope, then the members of `blip` appear as if they were declared in global scope.

When a namespace is injected into an enclosing scope, it is possible for names in the namespace to conflict with other names defined in that (enclosing) scope. For example, inside manip, the `blip` member `j` conflicts with the global object named `j`. Such conflicts are permitted, but to use the name, we must explicitly indicate which version is wanted. Any unqualified use of `j` within manip is an *ambiguous error*.

#### Headers and using Declarations or Directives

A header that has a using directive or declaration at its top-level scope injects names into every file that includes the header. Header files should not contain using directives or using declarations except inside functions or namespaces.

### Classes, Namespaces, and Scope

Name lookup for names used inside a namespace follows the normal lookup rules: The search looks outward through the enclosing scopes. An enclosing scope might be one or more nested namespaces, ending in the all-encompassing global namespace. Only names that have been declared before the point of use that are in blocks that are still open are considered:

```C++
namespace A
{
    int i;

    namespace B
    {
        int i; // hides A::i within B
        int j;

        int f1()
        {
            int j;      // j is local to f1 and hides A::B::j
            return i;   // returns B::i
        }
    } // namespace B is closed and names in it are no longer visible

    int f2()
    {
        return j;   // error: j is not defineds
    }

    int j = i;  // initialized from A::i
}
```

When a class is wrapped in a namespace, the normal lookup still happens: When a name is used by a member function, look for that name in the *member* first, then within the class (including base classes), then look in the enclosing scopes, one or more of which might be a namespace:

```C++
namespace A
{
    int i;
    int k;

    class C1
    {
    public:
        C1(): i(0), j(0) { }    // ok: initializes C1::i and C1::j
        int f1() { return k; }  // returns A::k
        int f2() { return h; }  // error: h is not defined
        int f3();
    private:
        int i;                  // hides A::i within C1
        int j;
    };

    int h = i;      // initialized from A::i
}

// member f3 is defined outside class C1 and outside namespace A
int A::C1::f3()
{
     return h; // ok: returns A::h
}
```

With the exception of member function definitions that appear inside the class body, scopes are always searched **upward**; names must be declared before they can be used. Hence, the `return` in `f2` will not compile. Similarly, the use of `h` inside `f3` is okay, because `f3` is defined after `A::h`.

#### Argument-Dependent Lookup and Parameters of Class Type

Consider the following simple program:

```C++
std::string s;
std::cin >> s;
```

As we know, this call is equivalent to:

```C++
// not std::operator>>, here we call the operator functiont without a std:: qualifier
operator>>(std::cin, s);
```

This `operator>>` function is defined by the string library, which in turn is defined in the `std` namespace. Yet we can we call `operator>>` **without** an `std::` qualifier and without a using declaration.

We can directly access the output operator because there is an important exception to the rule that names defined in a namespace are hidden:

When we pass an object of a class type to a function, the compiler searches the namespace in which the argument's class is defined in addition to the normal scope lookup. This exception also applies for calls that pass pointers or references to a class type.

In this example, when the compiler sees the "call" to operator>>, it looks for a matching function in the current scope, including the scopes enclosing the output statement. In addition, because the `>>` expression has parameters of class type, the compiler also looks in the namespace(s) in which the *types* of `cin` and `s` are defined. Thus, for this call, the compiler looks in the `std` namespace, which defines the `istream` and `string` types. When it searches `std`, the compiler finds the string output operator function.

#### Friend Declarations and Argument-Dependent Lookup

The friend declaration does not make the friend visible.However, an otherwise undeclared class or function that is first named in a friend declaration is assumed to be a member of the closest enclosing namespace.

```C++
namespace A
{
    class C
    {
        // two friends; neither is declared apart from a friend declaration
        // these functions implicitly are members of namespace A

        friend void f2();           // won't be found, unless otherwise declared
        friend void f(const C&);    // found by argument-dependent lookup
    };
}

int main()
{
    A::C cobj;
    f2();       // error: A::f2 not declared
    f(cobj);    // ok: finds A::f through the friend declaration in A::C
}
```

### Overloading and Namespaces

#### Argument-Dependent Lookup and Overloading

Name lookup for functions that have class-type arguments includes the namespace in which each argument's class is defined. This rule also impacts how we determine the candidate set.

Each namespace that defines a class used as an argument (**and those that define its base classes**) is searched for candidate functions. Any functions in those namespaces that have the same name as the called function are added to the candidate set. These functions are added even though they otherwise are not visible at the point of the call:

```C++
namespace NS
{
    class Quote { /* ... */ };
    void display(const Quote&) { /* ... */ }
}

// Bulk_item's base class is declared in namespace NS
class Bulk_item : public NS::Quote { /* ... */ };

int main()
{
    Bulk_item book1;
    display(book1);
    return 0;
}
```

The function declared in `NS` namespace will be added to the candidate set also.

#### Overloading and using Declarations

To understand the interaction between **using declarations** and **overloading**, it is important to remember that a using declaration declares a **name**, not a specific function:

```C++
using NS::print(int);   // error: cannot specify a parameter list
using NS::print;        // ok: using declarations specify names only
```

When we write a using declaration for a function, all the versions of that function are brought into the current scope.

#### Overloading and using Directives

```C++
namespace libs_R_us
{
    extern void print(int);
    extern void print(double);
}

// ordinary declaration
void print(const std::string &);

// this using directive adds names to the candidate set for calls to print:
using namespace libs_R_us;

// the candidates for calls to print at this point in the program are:
// print(int) from libs_R_us
// print(double) from libs_R_us
// print(const std::string &) declared explicitly
void fooBar(int ival)
{
    print("Value: ");       // calls global print(const string &)
    print(ival);            // calls libs_R_us::print(int)
}
```

Differently from how using declarations work, it is not an error if a using directive introduces a function that has the same parameters as an existing function. As with other conflicts generated by using directives, there is no problem unless we try to call the function without specifying whether we want the one from the namespace or from the current scope.

#### Overloading across Multiple using Directives

If many using directives are present, then the names from each namespace become part of the candidate set:

```C++
namespace AW
{
    int print(int);
}
namespace Primer
{
    double print(double);
}

// using directives create an overload set of functions from different namespaces
using namespace AW;
using namespace Primer;

long double print(long double);

int main()
{
    print(1);   // calls AW::print(int)
    print(3.1); // calls Primer::print(double)
    return 0;
}
```

## Multiple and Virtual Inheritance

### Multiple Inheritance

```C++
class Bear : public ZooAnimal
{
    /* ... */
};
class Panda : public Bear, public Endangered
{
    /* ... */
};
```

#### Derived Constructors Initialize All Base Classes

Constructing an object of derived type constructs and initializes all its base subobjects. As is the case for inheriting from a single base class a derived type's constructor initializer may initialize only its *direct base classes*:

```C++
// explicitly initialize both base classes
Panda::Panda(std::string name, bool onExhibit)
    :Bear(name, onExhibit, "Panda"),
     Endangered(Endangered::critical) { }

// implicitly uses the Bear default constructor to initialize the Bear subobject
Panda::Panda()
    : Endangered(Endangered::critical) { }
```

The order in which base classes are constructed depends on the order in which they appear in the class derivation list. The order in which they appear in the constructor initializer list is irrelevant.

#### Inherited Constructors and Multiple Inheritance

Under the new standard, a derived class can inherit its constructors from one or more of its base classes. It is an error to inherit the same constructor (i.e., one with the same parameter list) from more than one base class:

```C++
struct Base1
{
    Base1() = default;
    Base1(const std::string&);
    Base1(std::shared_ptr<int>);
};

struct Base2
{
    Base2() = default;
    Base2(const std::string&);
    Base2(int);
};

// error: D1 attempts to inherit D1::D1 (const string&) from both base classes
struct D1: public Base1, public Base2
{
    using Base1::Base1; // inherit constructors from Base1
    using Base2::Base2; // inherit constructors from Base2
};
```

A class that inherits the same constructor from more than one base class must define
its own version of that constructor:

```C++
struct D2: public Base1, public Base2
{
    using Base1::Base1; // inherit constructors from Base1
    using Base2::Base2; // inherit constructors from Base2

    // D2 must define its own constructor that takes a string
    D2(const string &s): Base1(s), Base2(s) { }
    D2() = default; // needed once D2 defines its own constructor
};
```

### Conversions and Multiple Base Classes

Under single inheritance, a pointer or a reference to a derived class can be converted automatically to a pointer or a reference to an accessible base class. The same holds true with multiple inheritance. A pointer or reference to any of an object's (accessible) base classes can be used to point or refer to a derived object.

```C++
// operations that take references to base classes of type Panda
void print(const Bear&);
void highlight(const Endangered&);
ostream& operator<<(ostream&, const ZooAnimal&);

Panda ying_yang("ying_yang");
print(ying_yang);               // passes Panda to a reference to Bear
highlight(ying_yang);           // passes Panda to a reference to Endangered
cout << ying_yang << endl;      // passes Panda to a reference to ZooAnimal
```

The compiler makes no attempt to distinguish between base classes in terms of a derived-class conversion. Converting to each base class is equally good. For example, if there was an overloaded version of print:

```C++
void print(const Bear&);
void print(const Endangered&);
```

an unqualified call to print with a Panda object would be a compile-time error:

```C++
Panda ying_yang("ying_yang");
print(ying_yang); // error: ambiguous
```

#### Lookup Based on Type of Pointer or Reference

As with single inheritance, the static type of the object, pointer, or reference determines which members we can use. If we use a `ZooAnimal` pointer, only the operations defined in that class are usable. The `Bear`-specific, `Panda`-specific, and `Endangered` portions of the `Panda` interface are invisible.

### Class Scope under Multiple Inheritance

Under multiple inheritance, if a name is found through more than one base class, then use of that name is ambiguous.

### Virtual Inheritance

Although the derivation list of a class may not include the same base class more than once, a class can inherit from the same base class more than once. It might inherit the same base indirectly from two of its own direct base classes, or it might inherit a particular class directly and indirectly through another of its base classes.

By default, a derived object contains a separate subpart corresponding to each class in its derivation chain. If the same base class appears more than once in the derivation, then the derived object will have more than one subobject of that type.

In C++ we solve this kind of problem by using **virtual inheritance**. Virtual inheritance lets a class specify that it is willing to share its base class. The shared base-class subobject is called a **virtual base class**. Regardless of how often the same virtual base appears in an inheritance hierarchy, the derived object contains only one, shared subobject for that virtual base class.

#### Using a Virtual Base Class

We specify that a base class is virtual by including the keyword virtual in the derivation list:

```C++
// the order of the keywords public and virtual is not significant
class Raccoon : public virtual ZooAnimal { /* ... */ };
class Bear : virtual public ZooAnimal { /* ... */ };
```

Here we’ve made ZooAnimal a virtual base class of both Bear and Raccoon.

```C++
class Panda : public Bear, public Raccoon, public Endangered {
    /* ... */
};
```

Here Panda inherits ZooAnimal through both its Raccoon and Bear base classes. However, because those classes inherited virtually from ZooAnimal, Panda has only one ZooAnimal base subpart.

#### Visibility of Virtual Base-Class Members

For example, assume class `B` defines a member named `x`; class `D1` inherits virtually
from `B` as does class `D2`; and class `D` inherits from `D1` and `D2`. From the scope of `D`, x is visible through both of its base classes. If we use `x` through a `D` object, there are three possibilities:

* If `x` is not defined in either `D1` or `D2` it will be resolved as a member in B; there is no ambiguity. A `D` object contains only one instance of `x`.
* If `x` is a member of `B` and also a member in one, but not both, of `D1` and `D2`, there is again no ambiguity—the version in the derived class is given precedence over the shared virtual base class, B.
* If `x` is defined in both `D1` and `D2`, then direct access to that member is ambiguous.

As in a nonvirtual multiple inheritance hierarchy, ambiguities of this sort are best resolved by the derived class providing its own instance of that member.

### Constructors and Virtual Inheritance

In a virtual derivation, the virtual base is initialized by the *most derived constructor*. In our example, when we create a Panda object, the Panda constructor alone controls how the ZooAnimal base class is initialized.

```C++
Panda::Panda(std::string name, bool onExhibit)
    : ZooAnimal(name, onExhibit, "Panda"),
      Bear(name, onExhibit),
      Raccoon(name, onExhibit),
      Endangered(Endangered::critical),
      sleeping_flag(false) { }
```

#### How a Virtuallly Inherited Object Is Constructed

The construction order for an object with a virtual base is slightly modified from the normal order: The virtual base subparts of the object are initialized first, using initializers provided in the constructor for the most derived class. Once the virtual base subparts of the object are constructed, the direct base subparts are constructed in the order in which they appear in the derivation list.

For example, when a Panda object is created:

* The (virtual base class) ZooAnimal part is constructed first, using the initializers specified in the Panda constructor initializer list.
* The Bear part is constructed next.
* The Raccoon part is constructed next.
* The third direct base, Endangered, is constructed next.
* Finally, the Panda part is constructed.

If the Panda constructor does not explicitly initialize the ZooAnimal base class,
then the ZooAnimal default constructor is used. If ZooAnimal doesn’t have a
default constructor, then the code is in error.
Note

* Virtual base classes are always constructed prior to nonvirtual base classes regardless of where they appear in the inheritance hierarchy.