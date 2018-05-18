# Specialized Tools and Techniques

## Controlling Memory Allocation

### Overloading `new` and `delete`

When the compiler sees a `new` or `delete` expression, it looks for the corresponding operator function to call. If the object being allocated (deallocated) has class type, the compiler first looks in the scope of the class, including any base classes. Otherwise, the compiler looks for a matching function in the global scope. (operator `new` and `delete` can't be declared inside a namespace)

We can use the scope operator to force a new or delete expression to bypass a class-specific function and use the one from the global scope. For example, `::new` will look only in the global scope for a matching operator new function. Similarly for `::delete`.

### The `operator new` and `operator delete` Interface

```C++
// these versions might throw an exception
void *operator new(size_t); // allocate an object
void *operator new[](size_t); // allocate an array
void *operator delete(void*) noexcept; // free an object
void *operator delete[](void*) noexcept; // free an array

// versions that promise not to throw;
void *operator new(size_t, nothrow_t&) noexcept;
void *operator new[](size_t, nothrow_t&) noexcept;
void *operator delete(void*, nothrow_t&) noexcept;
void *operator delete[](void*, nothrow_t&) noexcept;
```

When defined as members of a class, these operator functions are implicitly static. There is no need to declare them static explicitly, although it is legal to do so.

When we define our own `operator new` function, we can define additional
parameters. A new expression that uses such functions must use the *placement form* of new to pass arguments to these additional parameters.

Although generally we may define our version of operator new to have whatever parameters are needed, we may not define a function with the following form:

```C++
void *operator new(size_t, void*); // this version may not be redefined
```

### Placement `new` Expressions

```C++
new (place_address) type
new (place_address) type (initializers)
new (place_address) type [size]
new (place_address) type [size] { braced initializer list }
```

where place_address must be a pointer and the initializers provide (a possibly empty) comma-separated list of initializers to use to construct the newly allocated object.

When called with an address and no other arguments, placement new uses operator new(size_t, void*) to “allocate” its memory. This is the version of operator new that we are not allowed to redefine (§ 19.1.1, p. 822). This function does not allocate any memory; it simply returns its pointer argument.

## Run-Time Type Identification

### The dynamic_cast Operator

A dynamic_cast has the following form:

```C++
dynamic_cast<type*>(e)
dynamic_cast<type&>(e)
dynamic_cast<type&&>(e)
```

where `type` must be a class type and (ordinarily) names a class that has virtual functions. In the first case, e must be a valid pointer. in the second, `e` must be an lvalue; and in the third, e must not be an lvalue.

In all cases, the type of e must be either a class type that is publicly derived from the target type, a public base class of the target type, or the same as the target type. Otherwise, the cast fails.

We can do a `dynamic_cast` on a null pointer; the result is a null pointer of the requested type.

### The `typeid` Operator

The `typeid` operator can be used with expressions of any type. As usual, top-level const is ignored, and if the expression is a reference, typeid returns the type to which the reference refers. When applied to an array or function, however, the standard conversion to pointer is not done. That is, if we take typeid(a) and a is an array, the result describes an array type, not a pointer type.

When the operand is not of class type or is a class without virtual functions, then the typeid operator indicates the **static type** of the operand. When the operand is an **lvalue** of a class type that defines at least one virtual function, then the type is evaluated at **run time**.

```C++
Derived *dp = new Derived;
Base *bp = dp; // both pointers point to a Derived object

// compare the type of two objects at run time
if (typeid(*bp) == typeid(*dp)) {
// bp and dp point to objects of the same type
}

// test whether the run-time type is a specific type
if (typeid(*bp) == typeid(Derived)) {
// bp actually points to a Derived
}
```

### The `type_info` Class

There is no `type_info` default constructor, and the copy and move constructors and the assignment operators are all defined as deleted. Therefore, we cannot define, copy, or assign objects of type `type_info`. The only way to create a `type_info` object is through the `typeid` operator.

## Enumerations

Define a **scoped enumeration**:

```C++
enum class open_modes
{
    input, output, append
};
```

We define an unscoped enumeration by omitting the class (or struct) keyword. The enumeration name is optional in an unscoped enum:

```C++
enum color {red, yellow, green}; // unscoped enumeration

// unnamed, unscoped enum
enum {floatPrec = 6, doublePrec = 10, double_doublePrec =
10};
```

**Enumerators** are const and, if initialized, their initializers must be constant expressions. Consequently, each enumerator is itself a constant expression.

### Like Classes, Enumerations Define New Types

So long as the enum is **named**, we can define and initialize objects of that type. An enum object may be initialized or assigned only by one of its enumerators or by another object of the same enum type:

```C++
open_modes om = 2;       // error: 2 is not of type open_modes
om = open_modes::input;  // ok: input is an enumerator of open_modes
```

Objects or enumerators of an unscoped enumeration type are automatically converted to an integral type. As a result, they can be used where an integral value is required:

```C++
int i = color::red; // ok: unscoped enumerator implicitly converted to int
int j = peppers::red; // error: scoped enumerations are not implicitly converted
```

### Specifying the Size of an enum

Although each enum defines a unique type, it is represented by one of the built-in integral types. 

Under the new standard, we may specify that type by following the enum name with a colon and the name of the type we want to use:

```C++
enum intValues : unsigned long long
{
    charTyp = 255,
    shortTyp = 65535,
    intTyp = 65535,
    longTyp = 4294967295UL,
    long_longTyp = 18446744073709551615ULL
};
```

If we do not specify the underlying type, then by default scoped enums have `int` as the underlying type. There is no default for unscoped enums; all we know is that the underlying type is large enough to hold the enumerator values.

### Forward Declarations for Enumerations

Under the new standard, we can forward declare an enum. An enum forward declaration **must specify (implicitly or explicitly) the underlying size** of the enum:

```C++
// forward declaration of unscoped enum named intValues
enum intValues : unsigned long long;    // unscoped, must specify a type
enum class open_modes;                  // scoped enums can use int by default
```

## Pointer to Class Member

A **pointer to member** is a pointer that can point to a nonstatic member of a class.

To explain pointers to members, we'll use a version of the Screen class from §

```C++
class Screen
{
public:
    typedef std::string::size_type pos;

    char get_cursor() const { return contents[cursor]; }
    char get() const;
    char get(pos ht, pos wd) const;
private:
    std::string contents;
    pos cursor;
    pos height, width;
};
```

### Pointers to Data Members

```C++
// pdata can point to a string member of a const (or non const) Screen object
const string Screen::*pdata;
```

When we initialize (or assign to) a pointer to member, we say to which member it points. For example, we can make *pdata* point to the contents member of an unspecified Screen object as follows:

```C++
pdata = &Screen::contents;
```

Of course, under the new standard, the easiest way to declare a pointer to member is to use auto or decltype:

```C++
auto pdata = &Screen::contents;
```

### Using a Pointer to Data Member

Analogous to the member access operators, `.` and `->`, there are two pointer-tomember access operators, `.*` and `->*`, that let us supply an object and dereference the pointer to fetch a member of that object:

```C++
Screen myScreen, *pScreen = &myScreen;

// .* dereferences pdata to fetch the contents member from the object myScreen
auto s = myScreen.*pdata;

// ->* dereferences pdata to fetch contents from the object to which pScreen points
s = pScreen->*pdata;
```

Conceptually, these operators perform two actions:

* They dereference the pointer to member to get the member that we want; then, like the member access operators
* they fetch that member from an object (.*) or through a pointer (->*).

### Pointers to Member Functions

```C++
// pmf is a pointer that can point to a Screen member function that is const
// that returns a char and takes no arguments
auto pmf = &Screen::get_cursor;
```

As with normal function pointers, if the member is overloaded, we must distinguish which function we want by declaring the type explicitly.

For example, we can declare a pointer to the two-parameter version of get as

```C++
char (Screen::*pmf2)(Screen::pos, Screen::pos) const;
pmf2 = &Screen::get;
```

The parentheses around `Screen::*` in this declaration are essential due to precedence. Without the parentheses, the compiler treats the following as an (invalid) function declaration.

```C++
// error: nonmember function p cannot have a const qualifier
char Screen::*p(Screen::pos, Screen::pos) const;
```

Unlike ordinary function pointers, there is no automatic conversion between a member function and a pointer to that member:

```C++
// pmf points to a Screen member that takes no arguments and returns char
pmf = &Screen::get; // must explicitly use the address-of operator
pmf = Screen::get;  // error: no conversion to pointer for member functions
```

### Using a Pointer to Member Function

```C++
Screen myScreen,*pScreen = &myScreen;
// call the function to which pmf points on the object to which pScreen points
char c1 = (pScreen->*pmf)();
// passes the arguments 0, 0 to the two-parameter version of get on the object
myScreen
char c2 = (myScreen.*pmf2)(0, 0);
```

Because of the relative precedence of the call operator, declarations of pointers to member functions and calls through such pointers must use parentheses: `(C::*p)(parms)` and `(obj.*p)(args)`.

## Nested Classes

A class can be defined within another class. Such a class is a **nested class**, also referred to as a **nested type**.

A nested class defines a type member in its enclosing class. As with any other member, the enclosing class determines access to this type.

* A nested class defined in the public part of the enclosing class defines a type that may be used anywhere.
* A nested class defined in the protected section defines a type that is accessible only by the enclosing class, its friends, and its derived classes.
* A private nested class defines a type that is accessible only to the members and friends of the enclosing class.

### Defining a Nested Class outside of the Enclosing Class

As with member functions, nested classes **must be declared inside the class** but can be defined either inside or outside the class.

When we define a nested class outside its enclosing class, we must qualify the name of the nested class by the name of its enclosing class:

```C++
// we're defining the QueryResult class that is a member of class TextQuery
class TextQuery::QueryResult
{
    // in class scope, we don't have to qualify the name of the QueryResult parameters
    friend std::ostream&
    print(std::ostream&, const QueryResult&);

public:
    // no need to define QueryResult::line_no; a nested class can use a member
    // of its enclosing class without needing to qualify the member's name
    QueryResult(std::string,
                std::shared_ptr<std::set<line_no>>,
                std::shared_ptr<std::vector<std::string>>);
    // other members
};
```

### Defining the Members of a Nested Class

```C++
// defining the member named QueryResult for the class named QueryResult
// that is nested inside the class TextQuery
TextQuery::QueryResult::QueryResult(
    string s,
    shared_ptr<set<line_no>> p,
    shared_ptr<vector<string>> f)
: sought(s), lines(p), file(f) { }
```

### Nested-Class static Member Definitions

```C++
// defines an int static member of QueryResult
// which is a class nested inside TextQuery
int TextQuery::QueryResult::static_mem = 1024;
```

As we've seen, a nested class is a **type member** of its enclosing class. Members of the enclosing class can use the name of a nested class the same way it can use any other type member.

Because QueryResult is nested inside TextQuery, the `query` member of TextQuery can refer to the name QueryResult directly:

```C++
// return type must indicate that QueryResult is now a nested class
TextQuery::QueryResult
TextQuery::query(const string &sought) const
{
    // we'll return a pointer to this set if we don't find sought
    static shared_ptr<set<line_no>> nodata(new set<line_no>);
    // use find and not a subscript to avoid adding words to wm!
    auto loc = wm.find(sought);
    if (loc == wm.end())
        return QueryResult(sought, nodata, file); // not found
    else
        return QueryResult(sought, loc->second, file);
}
```

## `union`: A Space-Saving Class

A union is a special kind of class. A union may have multiple data members, but at any point in time, only one of the members may have a value. When a value is assigned to one member of the union, all other members become undefined. The amount of storage allocated for a union is at least as much as is needed to contain its largest data member. Like any class, a union defines a new type.

A union cannot have a member that is a reference, but it can have members of most other types.

A union may define member functions, including constructors and destructors. However, a union may **not** inherit from another class, nor may a union be used as a base class. As a result, **a union may not have virtual functions**.

### Using a union Type

```C++
Token first_token = {'a'};  // initializes the cval member
Token last_token;           // uninitialized Token object
Token *pt = new Token;      // pointer to an uninitialized Token object
```

If an initializer is present, it is used to initialize the first member.

### Anonymous `union`s

An anonymous union is an unnamed union that does not include any declarations between the close curly that ends its body and the semicolon that ends the union definition (§ 2.6.1, p. 73). When we define an anonymous union the compiler **automatically creates an unnamed object** of the newly defined union type:

```C++
// anonymous union
union
{
    char cval;
    int ival;
    double dval;
}; // defines an unnamed object, whose members we can access directly
cval = 'c'; // assigns a new value to the unnamed, anonymous union object
ival = 42; // that object now holds the value 42
```

The members of an anonymous union are directly accessible in the scope where the anonymous union is defined.
An anonymous union cannot have private or protected members, nor can an anonymous union define member functions.

### `union`s with Members of Class Type

When we switch the union to a member of class type, we must run a constructor for that member's type; when we switch from that member, we must run its destructor.

## Local Classes

All members, including functions, of a local class **must be completely defined inside the class** body. As a result, local classes are much less useful than nested classes.

Similarly, a local class is **not permitted** to declare static data members, there being no way to define them.

### Local Classes May Not Use Variables from the Function’s Scope

The names from the enclosing scope that a local class can access are limited. A local class can access **only**

* type names
* static variables
* enumerators

defined within the enclosing local scopes. A local class may not use the ordinary local variables of the function in which the class is defined:

```C++
int a, val;         // global `val`

void foo(int val)   // local `val`
{
    static int si;
    enum Loc { a = 1024, b };

    // Bar is local to foo
    struct Bar
    {
        Loc locVal; // ok: uses a local type name
        int barVal;
        void fooBar(Loc l = a) // ok: default argument is Loc::a
        {
            barVal = val;   // error: val is local to foo
            barVal = ::val; // ok: uses a global object
            barVal = si;    // ok: uses a static local object
            locVal = b;     // ok: uses an enumerator
        }
    };
    // . . .
}
```

* Normal Protection Rules Apply to Local Classes
* Name Lookup within a Local Class

### Nested Local Classes

It is possible to nest a class inside a local class. In this case, the nested class definition can appear outside the local-class body. However, the nested class must be defined in the **same** scope as that in which the local class is defined.

```C++
void foo()
{
    class Bar
    {
    public:
        // ...
        class Nested; // declares class Nested
    };

    // definition of Nested
    class Bar::Nested
    {
        // ...
    };
}
```

## Inherently Nonportable Features

### Bit-fields

A class can define a (nonstatic) data member as a `bit-field`. The memory layout of a `bit-field` is machine dependent

A bit-field must have **integral or enumeration type**. Ordinarily, we use an unsigned type to hold a bit-field, because the behavior of a signed bit-field is implementation defined.

```C++
typedef unsigned int Bit;
class File
{
    Bit mode: 2;        // mode has 2 bits
    Bit modified: 1;    // modified has 1 bit
    Bit prot_owner: 3;  // prot_owner has 3 bits
    Bit prot_group: 3;  // prot_group has 3 bits
    Bit prot_world: 3;  // prot_world has 3 bits
    // operations and data members of File
    // ...
public:
    // file modes specified as octal literals
    enum modes { READ = 01, WRITE = 02, EXECUTE = 03 };
    File &open(modes);
    void close();
    void write();
    bool isRead() const;
    void setWrite();
};
```

The address-of operator (&) **cannot** be applied to a bit-field, so there can be no pointers referring to class bit-fields.

## volatile qualifier

An object should be declared `volatile` when its value might be changed in ways outside the control or detection of the program. The `volatile` keyword is a directive to the compiler that it should not perform optimizations on such objects.

The `volatile` qualifier is used in much the same way as the const qualifier. It is an additional modifier to a type:

```C++
volatile int display_register;  // int value that might change
volatile Task *curr_task;       // curr_task points to a volatile object
volatile int iax[max_size];     // each element in iax is volatile
volatile Screen bitmapBuf;      // each member of bitmapBuf is volatile
```

In the same way that a class may define const member functions, it can also define member functions as volatile. **Only volatile member functions may be called on volatile objects**.

## Linkage Directives: extern "C"

The compiler checks calls to functions written in another language in the same way that it handles ordinary C++ functions. However, the compiler typically must generate different code to call functions written in other languages. C++ uses `linkage directives` to indicate the language used for any non-C++ function.

### Declaring a Non-C++ Function

A linkage directive can have one of two forms: single or compound. Linkage directives **may not** appear inside a class or function definition. The same linkage directive must appear on every declaration of a function.

```C++
// illustrative linkage directives that might appear in the C++ header <cstring>
// single-statement linkage directive
extern "C" size_t strlen(const char *);

// compound-statement linkage directive
extern "C"
{
    int strcmp(const char*, const char*);
    char *strcat(char*, const char*);
}
```

### Linkage Directives and Headers

```C++
// compound-statement linkage directive
extern "C" {
    #include <string.h> // C functions that manipulate C-style strings
}
```

Linkage directives can be nested, so if a header contains a function with its own linkage directive, the linkage of that function is unaffected.

### Pointers to extern "C" Functions

The language in which a function is written is part of its type. Hence, every declaration of a function defined with a linkage directive must use the same linkage directive. Moreover, pointers to functions written in other languages must be declared with the same linkage directive as the function itself:

```C++
// pf points to a C function that returns void and takes an int
extern "C" void (*pf)(int);
```

### Linkage Directives Apply to the Entire Declaration

When we use a linkage directive, it applies to the function and any function pointers used as the return type or as a parameter type:

```C++
// f1 is a C function; its parameter is a pointer to a C function
extern "C" void f1(void(*)(int));
```

Because a linkage directive applies to all the functions in a declaration, we must use a type alias if we wish to pass a pointer to a C function to a C++ function:

```C++
// FC is a pointer to a C function
extern "C" typedef void FC(int);
// f2 is a C++ function with a parameter that is a pointer to a C function
void f2(FC *);
```
