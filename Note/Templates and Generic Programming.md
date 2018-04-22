# Templates and Generic Programming

## Defining a Template

### Function templates

A fucntion template is a formula from which we can generate type-specific versions of that function.

* In a template definition, the template parameter list cannot be empty
* The compiler uses the deduced template parameter(s) to **instantiate** a specific version of the function to us

```C++
template <typename T>
int compare(const T &lhs, const T &rhs)
{
    if (lhs < rhs) return -1;
    if (rhs < lhs) return 1;
    return 0;
}
// instantiates int compare(const int&, const int&);
cout << compare(0, 1) << endl;
```

#### Nontype Template Parameters

A nontype parameter represent a value rather than a type. When the template is instantiated, nontype parameters are replaced with value supplied by the user or deduced by the complier. These values must be **constant expressions**.

```C++
template <unsigned N, unsigned M>
int compare(const char (&str1)[N], const char (&str2)[M])
{
    return strcmp(str1, str2);
}

compare("hi", "mom");
// the compiler instantiate
int compare(const char (&)[3], const char (&)[4]);
```

* A nontype parameter may be an integral type, or a pointer or (lvalue) reference to an obj or to a function type. Argument bound to a pointer or reference nontype parameter must have **static lifetime**. A poiner parameter can also be instantiated by a `nullptr` or a zero-valued constant expression
* A template nontype parameter is a constant value inside the templte definition and can be used when constant expressions are required.
* Template programs should try to minimize the number of requirements placed on the argument types.

```C++
// more type independent and portable by using less

// version of compare that will be correct even if used pointers(comparasion
// between unrelated pointers is UB, but less<T> sort them by phisycal address)
template <typename T>
int compare (const T &lhs, const T&rhs)
{
    if (less<T>()(v1, v2)) return -1;
    if (less<T>()(v2, v1)) return 1;
    return 0;
}
```

#### Template Compilation

To generate an instantiation, the compiler needs to have the code that defines a function template or class template member function.
As a result, defintions of function templates and member functions of class template are ordinarily put into **head files**.

Templates contains two kinds of names:

* Those that do not depend on a template parameter
* Those that do depend on the template parameter

### Class Templates

Class templates differ from function templates in that the compiler cannot deduce the template parameter type(s) for a class template.

Each instantiation of a class template constitutes an independent class. The type `vector<string>` has no relationship to, or any special access to, the member of any other `vector` type.

If a member function isn't used, it is **not instantiated**. The fact that members are instantiated only if we use them lets us instantiate a class with a type that may not meet the requirements for some of the template's operation.

There is one exception to the rule that we must supply template arguments when we use template type. Inside the scope of the class template itself, we may use the name of the templte without arguments.

```C++
template <typename T>
class Vec
{
public:
    Vec operator++(int); // use Vec without argument
};

// the return type appears outside the scope of the class, we must specify the return type with template argument
template <typename T>
Vec<T> Vec<T>::operator++(int)
{
    Vec temp = *this;// we are in the class scope now,
                     //so do not need to repeat the templte argument
    ++*this;
    return tmp;
}
```

#### Class Templates and Friends

* a class template that has a nontemplate friend grants that friend access to all the instantiations of the template.
* when the friend itself is a template, the class granting friendship controls whether friendship includes all instantiations of the templte or only specific instantiation(s)

##### One-to-One Friendship

```C++
// forward declaration needed for friend dclarations in Blob
template <typename> class BlobPtr;
template <typename> class Blob;
template <typename T>
    bool operator==(const Blob<T>&, const Blob<T>&);

template <typename T> class Blob
{
    friend class BlobPtr<T>;
    friend bool operator==<T>(const Blob<T>&, const Blob<T>&);
};

Blob<char> ca;// BlobPtr<char> and operator==<char> are friends
Blob<int> ia; // BlobPtr<int> and operator==<int> are friends
```

##### General and Specific Templtate Friendship

* Forward declaration is necessary to befriend a **specific instantiation** of a template
* No forward declaration required when we befriend **all instantiations** of a template

```C++
// forward declaration necessary to befriend a specific instantiation of a template
template <typename T> class Pal;

class C
{
    friend class Pal<C>; // Pal instantiated with class C is a friend to C

    // all instances of Pal2 are friends
    // no forward declaration required when we befriend all instantiations
    template <typename T>
    friend class Pal2;
};

template <typename T>
class C2
{
    // each instantiation of C2 has the same instance of Pal as a friend
    friend class Pal<T>;

    // all instances of Pal2 are friends of each instance of C2
    template <typename X>
    friend class Pal2;

    // Pal3 is a nontemplate class that is a friend to every instance of C2
    friend class Pal3;
}
```

* To allow all instantiations as friend, the friend declaration must use template parameter(s) differ from those used by the class itself.
* Under the new standard, we can make a template **type parameter** a friend:

```C++
template <typename Type> class C{
    friend Type;
}
```

* We can define a type alias for a class template:

```C++
template<typename T> using twin = pair<T, T>
twin<string> authors;// authors is a pair<string, string>
```

* When we define a template type alias, we can fix one or more of the template parameters:

```C++
template <typename T> using partNo = pair<T, unsigned>
partNo<string> books; // books is a pair<string, unsigned>
```

### Template Parameters

Unlike most other contexts, however, a name used as a template parameter may not be reused with in the template:

```C++
typedef double A;
template <typename A, typename B> void f(A a, B b)
{
    A tmp = a; // tmp has same type as the template parametre A, not double
    double B;  // error: redeclares template parameter B
}
```

* Because a parameter name cannot be reused, the name of a templte parameter can appear only once with in a given template parameter list:

```C++
// error: illegal reuse of template parameter V
template <typename V, typename V> // ...
```

#### Templte Declarations

As with function parameters, the name of a template parameter need not be the same across the declaration(s) and the definition of the same template:

```C++
// declaration
template <typename T> T calc(const T&);
template <typename U> U calc(const U&);

// definition
template <typename Type>
Type calc(const Type &a) { /* ... */ } // ok
```

Declarations for all the templates needed by a given file usually should appear together at the beginning of file before any code that use those names.

#### Default Template arguments

We can supply **default template arguments** for both function and class templates.

```C++
template <typename T, typename Compare = less<T>>
int compare (const T &lhs, const &rhs, Compare cmp = Compare())
{
    if (cmp(v1, v2)) return -1;
    if (cmp(v2, v1)) return 1;
    return 0;
}
```

#### Template Default Arguments and Class Template

Whenever we use a class template, we must always follow the template's name with brackets. In particular, if a class template provides default arguments for all of its template parameters, and we want to use those defaults, we must put an empty bracket pair following the template's name.

```C++
template <typename T = int> class Numbers{
public:
    Numbers(T v = 0): val(0){}
private:
    T val;
};
Numbers<long double> lots_of_precision;
Numbers<> average_precision;// empty <> says we want the default type
```

### Member Templates

A class-either an ordinary class or a class template—may have a member function that itself a template. Such members are refered to as **member templates**. Member templates may not be virtual

#### Member Templates of Class Templates

We can also define a member template of a class template. In this case, both the class and the member have their own, *independent*, template parameters.

```C++
template <typename Val> class Vec{
    template <typename Iter> Vec(Iter b, Iter e);
};
template <typename Val>
template <typename Iter>
Vec<Val>::Vec(Iter b, Iter e){/* ... */}

```

Unlike ordinary function members of class template, member templates are function templates. When we define a member template outside the body of a class template, we must provide the template parameter list for the class template and the function template. The parameter list for the class template comes first.

### Controlling Instantiations

The fact that instantiations are generated when a template is used means that the same instantiation may appear in multiple object files. When two or more separately compiled source files use the same template with the same template arguments, there is an instantiation of that template in each of those files.

* We can avoid this overhead through an **explicit instantiation**. An explicit instantiation has the form :

```C++
extern template declaration;    // instantiation declaration
template declaration;           // instantiation definition
```

For example:

```C++
extern template class Vec<string>               // declaration
template int compare(const int&, const int&);   // definition
```

* When the compiler seen an `extern` template declaration, it will not generate code for that instantiation in that file.
* Declaring an instantiation as `extern` promise that there will be a non`extern` use of that instantiation elsewhere in the program.
* There may be several `extern` declarations for a given instantiation but there must be exactly one definition for that instantiation
* Because the compiler automatically instantiates a template when we use it, the `extern` declaration must appear before any code that use the instantiation:

```C++
extern template class Blob<string>
extern template int compare (const int &, const int &);

Blob<string> sa1, sa2; // instantiation will appear elsewhere

// Blob<int> and its initializer_list ctor instantiated in this file
Blob<int> a1 = {0, 1, 2, 3};
Blob<int> a2(a1);// copy ctor instantiated in this file

int i = compare(a1[0], a2[0]);// instantiation will appear elsewhere
```

#### Instantiation Definition Instantiate All Members

An instantiation definition for a class template instantiates *all* the members of that template including inline members. Consequently, we can use explicit instantiation only for types that can be used with all the members of that template.

* Small Test:
* For each labeld statement explain what, if any, instantiations happen. If a template is instantiated, explain why; if not, explain why not.

```C++
template <typename T> class Stack{};

void f1(Stack<char>);               a)
class Exercise
{
    Stack<double> &rsd;             b)
    Stack<int> si;                  c)
};
int main()
{
    Stack<char> *sc;                d)
    f1(*sc);                        e)
    int i = sizeof(Stack<string>);  f)
}
```

* Ans:
* instantiation happens in a, b, c, f, since template are used in these statement
* instantiation not happens in d, e, sice template instantiation they used is already instantiated

## Template Argument Deduction

The process of determining the template arguments from the function arguments is known as **template argument dedcution**

### Conversions and Template Type Parameter

Function parameters whose type uses a template type parameter have special initialization rules. Only a very limited number of conversions are automatically applied to such arguments. Rather than converting the arguments, the compiler generates a new instantiation.
As usual, top-level `const`s are ignored when we copy an object. The only other conversions performed in a call to a function template are :

* `const` conversions: A function parameter that is a reference (or pointer) to a `const` can be passed as a reference (or pointer) to a non`const` obj
* Array- or function-to-pointer conversion: if the function parameter is **not** a reference type, than the normal pointer conversion will be applied to arguments of array or function type. An array argument will be converted to a pointer to its first element. Similarly, a function argument will be converted to a pointer to the function's type.

other conversions, such as the arithmetic conversions, derived-to-base, and user-defined conversions, are not preformed.

```C++
template <typename T> T fobj(T, T);               // arguments are copied
template <typename T> T fref(const T &, const T&) // arguments are references

string s1("a value");
const string s2("another value");
fobj(s1, s2); // calls fobj(string, string); top-level const is ignored
fref(s1, s2); // calls fref(const string&, const string&)
              // uses premissible conversion to const on s1

int a[10], b[42];
fobj(a, b); // calls f(int*, int*)
fref(a, b); // error: array types don't match
```

#### Normal Conversions Apply for Ordinary Arguments

A function template can have parameters that are defined using ordinary types—that is, types that do not involve a template type parameter. Such arguments have no special processing; they are converted as usual to the corresponding type of the parameter. For example:

```C++
template <typename T> ostream& print(ostream &os, const T &obj)
{
    return os << obj;
}

print(cout, 42); // instantiates print(ostream&, int)
ofstream f("output");
print(f, 10);    // uses print(ostream&, int); converts f to ostream&.
                 // not instantiates a new function
```

### Specifying an Explicit Template Argument

We can let the user to control the type of return by defining a third template parameter to represent the return type.

```C++
template <typename T1, typename T2, typename T3>
T1 sum(T2, T3);
```

In this case, there is no argument whose type can be used to deduce the type of `T1`. The caller must provide a **explicit template argument** for this parameter on each call to sum. Explicit template arguments are specified inside angle brackets after the function name and before the argument list:

```C++
// T1 is specified; T2 and T3 are inferred from the argument types
auto val3 = sum<long long>(i, lng); // long long sum(int, long)
```

* Explicit template argument(s) are matched to corresponding template parameter(s) from the left to right
* The first template argument is matched to the first template parameter, the second argument is matched to the second template parameter, and so on.
* An explicit template argument may be ommited only for the trailing(right-most) parameters, and then only if these can be deduced from the function parameters

If our `sum` function had been written as

```C++
// poor design: user must explicity specify all three template parameters>
template <typename T1, typename T2, typename T3>
T3 alternative_sum(T2, T1);

// error: can't infer initial template parameters
auto val3 = alternative_sum<long long>(i, lng);
// ok: all three parameters are explicity specified
auto val2 = alternative_sum<long long, int, long>(i, lng);
```

### Normal Conversions Apply for Explicitly Specified Arguments

Normal conversions also apply for arguments whose template type parameter is explicity specified:

```C++
long lng;
compare(lng, 1024);       // error: template parameters don't match
compare<long>(lng, 1024); // ok: instantiates compare(long, long)
compare<int>(lng, 1024);  // ok: instantiates compare(int, int)
```

If we explicitly specify the template parameter type, **normal conversions apply**. Thus the call to `compare<long>` is equivalent to calling a function taking two `const long&` parameters. The int parameter is automatically converted to `long`.

### Trailing Return Types and Type Transformation

```C++
template <typename Iter>
auto fcn(Iter first, Iter last) -> decltype(*beg)
{
    // process the range [first, last)
    return *begin; // return a reference to an element from the range
}
```

### Function Pointers and Argument Deduction

When we initialize or assign a fuction pointer from a function template, the compiler uses the type of the pointer to deduce the template argument(s).

```C++
template <typename T> int compare(const T&, const T&);
// pf1 points to the instantiation int compare(const int&, const int&)
int (*pf1)(const int&, const int&) = compare; // ok
```

The type of the parameters in `pf1` determines the type of the template argument for `T`. It is an error if the template arguments cannot be determined from the function pointer type:

```C++
void func(int(*)(const string&, const string&));
void func(int(*)(const int&, const int&));
func(compare); // error: which instantiation of compare?

// we can disambiguate the call to func by using explicit template arguments:
func(compare<int>); // ok, passing int compare(const int&, const int&)
```

### Template Argument Deduction and References

#### Reference Collapsing and Rvale Reference Parameters

```C++
template <typename T> void f(T&&);
f3(42); // argument is rvalue of type int; template parameter T is int
```

asssumig `i` is an int object, we might think that a call such as `f3(i)` would be illegal. After all, `i` is an lvalue, and normally we cannot bind an rvalue reference to an lvalue. However the language defines two exceptions to normal binding rules that allow this kind of usage.

* The first exceptions: When we pass an lvalue to a function parameter that is an **rvalue reference** to a template type parameter, the compiler deduces the template type parameter as the argument type's lvalue reference type.

```C++
int i = 0;
const int ci = 0;
f3(i);  // instantiate as T is int& (lvalue reference to int)
f3(ci); // argument is an lvalue, tempalte parameter T is const T&
```

* Seconde, if we indirectly (through type alias or template type parameter) create a **reference to a reference**, then those reference "**collapse**", in all but one case, the references collapse to form an ordinary lvalue reference type. The new standard, expanded the collapsing rules to include rvalue references. References collapse to form an rvalue reference only in the specific case of an rvalue reference to an rvalue reference. That is, for a given type X:
  + X& &, X& &&, and X&& & all collapse to type X&
  + The type X&& && collapses to X&&

#### Writing Template Functions with Rvalue Reference Parameter

The fact that the template parameter can be deduced to a reference type can have surprising impacts on the code inside the template.

```C++
template <typename T> void f3(T&& val)
{
    T t = val;          // copy or binding a reference
    t = doSomething(t); // does the argument change only t or val and t
    if (val == t){ /* ... */ } //always true if T is a reference type
}
```

Even though we cannot implicitly convert an lvalue to an rvalue reference, we can explicitly cast an lvalue to an rvalue reference using `static_cast`.
Binding a rvalue reference to an lvalue gives code that operates on the rvalue reference permission to clobber the lvalue.

### Fowarding

Some functions need to forward one or more of their arguments with their types **unchanged** to another, forward-to, function. In such cases, we need to preserve everything about the forwarded arguments, including whether or not the argument type is `const`, and whether the argument is an lvalue or rvalue.
As an example, we'll write a function that take a callable expression and two additional argument. Our function will call the given callable with the other two arguments in reverse order. The following is our first try:

```C++
// template that take a callable and two parameter
// and calls the given callable with the parameter "flipped"
// flip1 is an incomplete implementation: top-level const and references are lost
template <typename Func, typename T1, typename T2>
void flip1(Func f, T1 t1, T2 t2)
{
    f(t2, t1);
}
```

but if you want to use it to call a function that has a reference parameter:

```C++
void f(int v1, int &v2) // v2 is a reference
{
    cout << v1 << " " << ++v2 << endl;
}
```

Here `f` changes the value of the argument bound to `v2`. However, if we call `f` through `flip1`, the changes made by f do not affect the original argument:

```C++
f(42, i);        // f change its argument i
flip1(f, j, 42); // f called through flip1 leaves j unchanged (since t1 is passed by value)
```

#### Defining Function Parameters That Retain Type Information

To pass a reference through our flip function, we need to preserve the "lvalueness" of its given argument and `const`ness of the argument as well.

```C++
// keep the lvalueness and constness of
// argument passed to t1 and t2
template <typename Func, typename T1, typename T2>
void flip2(Func f, T1 &&t1, T2 &&t2)
{
    f(t2, t1);
}
```

A fucntion parameter that is an rvaltue reference to a template type parameter(i.e., T&&) preserves the `const`ness and lvalue/rvalue property of its corresponding argument.

This version of `flip2` works fine for functions that take lvalue references but cannot be used to call a function that has an rvalue reference parameter. For example:

```C++
void g(int &&i, int &j)
{
    cout << i << " " << j << endl;
}

// If we call g through flip2
flip2(g, i, 42); // error: can't initialize int&& from an lvalue, since t2 is an object which should be bound to a lvalue reference
```

#### Using std::forward to Preserve Type Information in a Call

* We can use a new library facility named `forward` to pass `flip2`'s parameters in a way that preserves the types of the originla arguments.
* Unlike `move`, `forward` must be called with an explicit argument.
* The return type of `forward<T>` is `T&&`
* Ordinarily, we use `forward` to pass a function parameter that is defined as an rvalue reference to a template type parameter. Through reference collapsing on its return type, `forward` preserves the lvalue/rvalue nature of its given argument

```C++
template <typename Type> intermediary(Type &&arg)
{
    finalFcn(std::forward<Type>(arg));
}
```

Because `arg` is an rvalue reference to a template type parameter, `Type` will represent all the type information in the argument passed to `arg`.

* When used with a function parameter that is an rvalue reference to template type parameter, `forward` preserves all the details about an argument's type
* As with `std::move`, it's a good idea not to provide a using declaration for `std::forward`.

## Overloading and Templates

Function templates can be overloaded by other templates or by ordinary, nontemplate functions.
Function matching is affected by the presence of function templates in the following ways:

* The candidate functions for a call include **any** function-template instantiation for which template argument deduction succeeds.
* The candidate functin templates are always viable, because template argument deduction will have eliminated any templates that are not viable.
* As usual, the viable functions (template and nontemplate) are ranked by the conversions, if any, needed to make the call. Of course, the conversions used to call a function template are quite limited.
* Also as usual, if exactly one function provides a better match than any of the others, that function is selected. However, if there are several functions that provide an equally good match, then:
  + If there is only one nontemplate function in the set of equally good matches, the nontemplate function is called.
  + If there are no nontemplate functions in the set, but there are mutiple function templates, and one of these templates is more specialized than any of the others, the more specialized function template is called.
  + Otherwise, the call is ambiguous

### Writing Overloaded Templates

As an example, we'll build a set of functions that might be useful during debugging. We'll start by writing the most general version of this function as a template that takes a reference to a `const` object:

```C++
// print any type we don't otherwise handle
template <typename T> string debug_rep(const T &t)
{
    ostringstream ret;
    ret << t; // uses T's output operator to print the representation of t
    return ret.str();// return a copy of the string to which ret is bound
}
```

Next, we'll define a version of `debug_rep` to print pointers:

```C++
// print pointers as their pointer value, followed by the object to which
// the pointer points
// NB: this function will not work properly with char*(because the IO libray
// defines a version of the << for char* values)
template <typename T> string debug_rep(T *p)
{
    ostringstream ret;
    ret << "pointer: " << p;        // print the pointer's own value
    if (p)
        ret << " " << debug_rep(*p);// print the value to which p points
    else
        ret << " null pointer";     // or indicate that p is null
    return ret.str();
}

string s("hi");
cout << debug_rep(s) << endl;// only the first version of debug_rep is viable
                             // the second version requires a pointer parameter
```

If we call `debug_rep` with a pointer:

```C++
cout << debug_rep(&s) << endl;
```

both functions generate viable instantiations:

* `debug_rep(const string* &)`, which is the instantiation of the first version of `debug_rep` with `T` bound to `string*`
* `debug_rep(string*)`, which is the instantiation of the second version of `debug_rep` with `T` bound to `string`.

The instantiation of the second version of debug_rep is an exact match for this call. The instantiation of the first version requires a conversion of the plain pointer to a pointer to `const`. So the second version run.

### Multiple Viable Templates

As another example, consider the following call:

```C++
const string *sp = &s;
cout << debug_rep(sp) << endl;
```

Here both templates are viable and both provide an exact match:

* `debug_rep(const string*&)`, the instantiation of the first version of the template with `T` bound to `const string*`
* `debug_rep(const string*)`, the instantiation of the second version of the template with `T` bound to `const string`

In this case normal function matching can't distinguish between these two calls. We might expect this call to be ambiguous. However, due to the special rules for overloaded function templates, this call will resolves to `debug_rep(T*)`, which is the more specialized template.
The reason for this rule is that without it, there would be no way to call the pointer version of `debug_rep` on a pointer to `const`. The problem is that the template `debug_rep(const T&)` can be called on essentially any type, including pointer types. Without this rule, calls that passed pointers to `const` would always be ambiguous

### Nontemplate and Template Overloads

For our next example, we'll define an ordinary nontemplate version of `debug_rep` to print strings inside double quote:

```C++
// print strings inside double quotes
string debug_rep(const string &s)
{
    return '"' + s + '"';
}
```

Now, when we call `debug_rep` on a string,

```C++
string s("hi");
cout << debug_rep(s) << endl;
```

there are two equally good viable functions:

* `debug_rep<string>(const string&)`, the first template with T bound to string
* `debug_rep(const string&)`, the ordinary, nontemplate function

In this case, both function have the same parameter list and are equally good match this call. For the same reasons that the most specialized of equally good function templates is prefered, a nontemplate function is preferred over equally good match(es) to a function template.

### Overloaded Templates and Conversions

There's one case we haven't covered so far: pointers to C-style character strings and string literal. Consider this call:

```C++
cout << debug_rep("hi world!") << endl; // calls debug_rep(T*)
```

Here all there of the debug_rep functions are viable:

* `debug_rep(const T&)`, with `T` bound to `char[10]`
* `debug_rep(T*)`, with `T` bound to `const char`
* `debug_rep(const string&)`, which requires a conversion from `const char*` to `string`

Both templates provide an exact match to the argument (array to pointer conversion is considered as an exact match in function-matching purpose). As before, the T* version is more specilized and is the one that will be selected.

If we want to handle character pointers as strings, we can define two more nontemplate overloads:

```C++
// convert the character pointers to string and call the string
// version of debug_rep
string debug_rep(char *str)
{
    return debug_rep(string(str));
}

string debug_rep(const char *str)
{
    return debug_rep(string(str));
}
```

### Missing Declaration Can Cause the Program to Misbehave

It is worth nothing that for `char*` version to work correctly, a declaration for `debug_rep(cosnt string&)` must be in scope when these functions are defined.

```C++
template <typename T> string debug_rep(const T &t);
template <typename T> string debug_rep(T *p);

// the following declaration must be in scope
// for the definition of debug_rep(char*) to do the right thing
string debug_rep(const string &);

string debug_rep(char *str)
{
    // if the declaration for the version that take a const string& is
    // not in scope the return will call debug_rep(const T&) with T
    // instantiated to string
    return debug_rep(string(str));
}
```

* **Tip**: Declare every function in an overload set before you define any of the functions. That way you don't have to worry whether the compiler will instantiate a call before it sees the function you intended to call.

## Variadic Templates

A **variadic template** is a template function or class that can take a varying nubmer of parameters. The varying parameters are known as a **parameter pack**. There are two kinds of parameter packs: A **template parameter pack** represents zero or more template parameters, and a **function parameter pack** represents zero or more function parameters.

```C++
// Args is a template parameter pack; rest is a function parameter pack
// Args represents zero or more template type parameters
// rest represents zero or more function parameters
template <typename T, typename... Args>
void foo(const T &t, const Args& ... rest);
```

For a variadic template, the compiler also deduces the number of parameters in the pack. For example, given these calls:

```C++
int i = 0;
double d = 3.14;
string s = "hello";

foo(i, s, 42, d);   // three parameters in the pack
foo(s, 42, "hi");   // two parameters in the pack
foo(d, s);          // one parameters in the pack
foo("hi");          // empty pack
```

the compiler will instantiate four different instances of `foo`

```C++
void foo(const int&, const string&, const int&, const double&);
void foo(const string&, const int&, const char[3]&);
void foo(const double&, const string&);
void foo(const char[3]&);
```

### The sizeof... Operator

When we need to know how many elements there are in a pack, we can use the `sizeof...` operator. Like `sizeof`, `sizeof...` returns a constant expression and does not evaluate its arguments.

```C++
template <typename ... Args> void g(Args ... args) {
    cout << sizeof...(Args) << endl; // number of type parameters
    cout << sizeof...(args) << endl; // number of function parameters
}
```

### Writing a Variadic Function Template

Variadic functions are often recursive. The first call processes the first argument in the pack and calls itself on the remaining arguments. To stop the recursion, we'll also need to define a nonvariadic `print` function that will take a stream and an object:

```C++
// function to end the recursion and print the last element
// this function must be declared before the variadic version of print is defined
template <typename T>
ostream &print(ostream &os, const T &t)
{
    return os << t; // no separator after the last element in the pack
}

template <typename T, typename... Args>
ostream &print(ostream &os, const T &t, const Args&... rest)
{
    os << t << ", ";            // print the first argument
    return print(os, rest...);  // recursive call; print the other arguments
}
```

### Pack Expansion

Aside from taking its size, the only other thing we can do with a parameter pack is to **expand** it. When we expand a pack, we also provide a **pattern** to be used on each expanded element. Expanding a pack separates the pack into its constituent elements, applying the pattern to each element as it does so. We trigger an expandsion by **putting an ellipsis(...) to the right of the pattern**. For example:

```C++
template <typename T, typename... Args>
ostream&
print(ostream &os, const T &t, const Args&... rest)// expand Args
{
    os << t << ", " << endl;
    return print(os, rest...);                     // expand rest
}
```

The expansion of `Args` applies the pattern `const Args &` to each element in the template parameter pack `Args`. The expansion of this pattern is a comma-separated list of zero or more parameter types, each of which will have the form `const type &`

The expansion of `rest` happens in the (recursive) call to `print`. The pattern is the name of the function parameter pack (i.e. `rest`). This pattern expands to a comma-separated list of the elements in the pack.

#### Understanding Pack Expansion

More complicated patterns are also possible:

```C++
// call debug_rep on each argument in the call to print
template <typename... Args>
ostream& errorMsg(ostream &os, const Args&... rest)
{
    // print (os, debug_rep(a1), debug_rep(a2), ..., debug_rep(an))
    return print(os, debug_rep(rest)...);
}
```

In contrast, the following pattern would fail to compile:

```C++
// passes the pack to debug_rep; print(os, debug_rep(a1, ... , an))
print(os, debug_rep(rest...));  // error: no matching function
```

### Forwarding Parameter Packs

Variadic functions often forward their parameters to other functions. Such functions typically have a form similar to :

```C++
// func has zero or more parameters each of which is
// an rvalue reference to a template parameter type
template <typename... Args>
void func(Args&&... args)    // expands Args as a list of rvalue references
{
    // the argument to work expands both Args and args
    work(std::forward<Args>(args)...);
}
```

Here we want to forward all of `func`'s arguments to another function named `work` that presumably does the real work of the function. Like our call to `construct` inside `emplace_back`, the expansion in the call to `word` expands both the template parameter pack and the function parameter pack.
Because the parameters to `func` are rvalue references, we can pass argument of any type to `func`; because we use `std::forward` to pass those arguments, all type information about those arguments will be preserved in the call to work.

## Template Specializations

A specialization is a separate definition of the template in which one or more template parameters are specified to have particular types.

### Defining a Function Template Specialization

When we specialize a function template, we must supply arguments for **every template parameter** in the original template. To indicate that we are specializing a template, we use the keyword `template` followed by an empty pair of angle brackets(<>). The empty brackets indicate that argument will be supplied for all the template parameters of the original template:

```C++
// special version of compare to handle pointers to character arrays
template <>
int compare(const char* const &p1, const char* const &p2)
{
    return strcmp(p1, p2);
}
```

The hard part in understanding this specialization is the function parameter types. When we define a specialization, the function parameter type(s) must match the corresponding types in a previously declared template. Here we are specializing :

```C++
template <typename T> int compare(const T&, const T&);
```

in which the function parameters are references to a `const` type.

We want to define a specialization of this function with `T` as `const char*`. So the type we need to use in our specialization is `const char * const &`, which is a reference to a `const` pointer to `const char`

### Function Overloading versus Template Specializations

Specializations **instantiate** a template; they do not overload it. As a result, specializations do not affect functions matching.

#### Ordinary Scope Rules Apply for Specialization

In order to specialize a template, a declaration for the **original template** must be in the scope. Moreover, a declaration for a specialization must be in scope before any code uses that instantiation of the template.
With ordinary classes and functions, missing declarations are (usually) easy to find—the compiler won't be able to process our code. However, if a specialization declaration is missing, the compiler will usually generate code using the original template.
It is an error for a program to use a specialization and an instantiation of  the original template with the same set of template arguments. However, it is an error that the compiler is unlikely to detect.

* Best Practice:
* Templates and their specializations should be declared in the same header file. Declaration for all the templates with a given name should appear first, followed by any specialization of those templates.

### Class Template Specializations

When we specialize a template, we must do so in the same namespace in which original template is defined

```C++
// open the std namespace so we can specialize std::hash
namespace std{
template <>
struct hash<Sales_data>
{
    using result_type = size_t;
    using argument_type = Sales_data;   // by default, this type needs ==
    size_t operator()(const Sales_data &s) const;
    // our class uses synthesized copy control and default ctor
};
size_t hash<Sales_data>::operator()(const Sales_data &s) const
{
    return hash<string>()(s.bookNo) ^
           hash<unsigned>()(s.units_sold) ^
           hash<double>()(revenue);
}
}// close the std namespace
```

To enable user of `Sales_data` to use the specialization of `hash`, we should define this specialization in the `Sales_data` header.

### Class-Template Partial Specializations

* A class template **partial specialization** is itself a template.
* We can partially specialize only a class template. We cannot partially specialize a function template.

```C++
// original, most general template
template <typename T> struct remove_reference{
    using type = T;
};

// partial specialization for lvalue and rvalue references
template <typename T> struct remove_reference<T&>
{
    using type = T;
};
template <typename T> struct remove_reference<T&&>
{
    using type = T;
};
```

* The specialization's template parameter list includes an entry for each template parameter whose type is not completely fixed by this specialization.
* After the class name, we specify arguments for the template parameters we are specializing. These arguments are listed inside angle brackets following the template name, correspond positionally to the parameters in the original template.

### Specializing Member but Not the Class

Rather than specializing the whole template, we can specialize just specific member function(s).

```C++
template <typename T> struct Foo{
    void Bar() {/* ... */}
}

template <>         // we're specializing a template
void Foo<int>::Bar()// we're specializing the Bar member of Foo<int>
{
    // do whatever specialized processing that applies for int
}

Foo<string> fs; // instantiates Foo<string>::Foo()
fs.Bar();       // instantiates Foo<string>::Bar()
Foo<int> fi;    // instantiates Foo<int>::Foo()
fi.Bar();       // use our specialization of Foo<int>::Bar()

```