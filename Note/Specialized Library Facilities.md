# Specialized Library Facilities

## The `tuple` Type

a `tuple` can be thought as a "quick and dirty" data structure

```C++
// define a tuple
tuple<size_t, size_t, size_t> threeD; // all three members set to 0
tuple<string, vector<double>, int, list<int>>
    someVal("constants", {3.14, 2.718}, 42, {0, 1, 2});
```

* The default `tuple` ctor value initializes each member.
* We can supply an initializer for each member as we do in the initialization of `someVal`. This `tuple` ctor is `explicit`, so we must use the direct initialization syntax:

Alternatively, similar to the `make_pair` function, the library defines a `make_tuple` function that generates a `tuple` object:

```C++
// instantiate make_tuple<const char *, int, double> function
auto item = make_tuple("0-999-7", 3, 20.00);
```

### Accessing the Members of a `tuple`

`get` returns a reference to the member of a `tuple`

```C++
auto book = get<0>(item);           // return the first member
auto cnt  = get<1>(item);           // return the second member
auto price = get<2>(item) / cnt;    // return the last member
get<2>(item) *= 0.8;
```

If we hava a `tuple` whose precise type details we don't know, we can use two auxilliary class templates to find the number and types of the `tuple`'s members:

```C++
typedef decltype(item) trans; // trans is the type of item

// return the number of members in object's of type trans
size_t sz = tuple_size<trans>::value;   // return 3

// cnt has the same type as the second member in item
tuple_element<1, trans>::type cnt = get<1>(item);   // cnt is an int
```

### Relational and Equality Operators

These operators execute pairwise on the members of the left-hand and right-hand `tuple`s. We can compare two `tuple`s **only if** they have the same number of members.

```C++
tuple<string, string> t_s_s("1", "2");
tuple<size_t, size_t> t_i_i(1, 2);
tuple<double, double> t_d_d(1.0, 2.0);

bool b = (t_s_s == t_i_i);      // error: can't compare int and a string
b = (t_i_i < t_d_d);            // ok
```

## The `bitset` Type

### Defining and Initializing `bitset`s

The `bitset` class is a class template that, has a fixed size. When we define a `bitset`, we say how many bits the `bitest` will contain:

```C++
bitset<32> bitvec(1U);  // 32 bits; low-order bit is 1, remaining bits are 0
```

The bits are numbered starting at 0. Thus, `bitvec` has bits numbered 0 through 31. The bit starting at 0 are referred to as the **low-order** bits, and those ending at 31 are referred to as **high-order** bits.

```C++
bitset<8> bitvec(1U);
cout << bitvec << endl;
cout << "At position 0: " <<  bitvec[0] << endl;
cout << "Before end position: " << bitvec[bitvec.size() - 1] << endl;
/* output :
00000001
At position 0: 1
Before end position: 0
*/
```

#### Initializing a `bitset` from an `unsigned` Value

If the size of the `bitset` is greater than the number of bits in an `unsigned long long`, then the remaining high-order bits are set to zero. If the size is less than the number of bits, then only the low-order bits from the given value are used.

```C++
// high-order bits from the initializer are discarded
bitset<13> bitvec1(0xbeef);     // bits are 1111011101111

// high-order bits are set to zero
bitset<20> bitvec2(0xbeef);     // bits are 0000101111011101111

// on machine with 64-bit long long 0ULL is 64 bits of 0, so ~0ULL is 64 bits of 1
bitset<128> bitvec3(~0ULL);     // bits 0 ... 63 are one, 64 ... 127 are zero
```

#### Initializing a `bitset` from a `string`

As usual, when we use strings to represent numbers, the characters with the **lowest indices** in the string correspond to the **high-order** bits, and vice versa.

```C++
bitset<32> bitvec4("1100");     // bits 2 and 3 are 1, all others are 0

string bits("111111100000");
bitset<32> bitvec5(bits, 5, 4); // 1100, start at pos 5, max_len is 4

// same as using a temporary string from the input
cin >> bitvec5;  // reads characters from istream into b, Reading stops when
                 // the next character is not a 0 or 1 or when b.size() bits
                 // have been read
```

* **Indicing**

```C++
bitset<4> bits(5);  // string representation: 0101
for (size_t i = 0; i < bits.size(); ++i)
    cout << bits[i];                    // from low-order to high-order: 1010

const bitset<4> bit_vec(2); // 10
auto bit = bit_vec[0];      // bit is of bool type

bitset<4> bit_vec1(2);      // 10
auto ref = bit_vec1[0];     // ref is reference to a bit in the bitset(i.e., a proxy type of one bit in memory)
```

* Retrieving the Value of a `bitset`

These operations throw an `overflow_error` exception if the value in `bitset` does not fit in the specific type

```C++
unsigned long long val = bitvec3.to_ulong();    // to_ulong, to_ullong
```

## Regular Expressions

The `regex` class represents a regular expression. The functions `regex_match` and `regex_search` determine whether a given character sequence matches a given `regex`.

* The `regex_match` returns `true` if the entire input sequence matches the expression;
* `regex_search` returns `true` if there is a substring in the input sequence that matches.

```C++
// find the characters ei that follows a character other than c
string pattern("[^c]ei");

// we want the whole word in which our pattern appears
pattern = "[[:alpha:]]*" + pattern + "[[:alpha:]]*";

regex r(pattern);       // construct a regex to find pattern
smatch results;         // define an object to hold the result of a search

// define a string that has text that does and doesn't match pattern
string test_str = "receipt freind theif receive";

// use r to find a match to pattern in the test_str
if (regex_search(test_str, results, r))
    cout << results.str() << endl;  // print the matching word (i.e., 'freind' here)
```

### Specifying Options for a `regex` Object

```C++
// one or more alphanumeric characters followed by a '.' followed by "cpp" or "cxx" or "cc"
regex r("[[:alnum:]]+\\.(cpp|cxx|cc)$", regex::icase);  // ignore case
```

Just as there are special characters in C++, regular-expression languages typically also have special characters. For example, the dot (.) character usually matches any character. As we do in C++, we can escape the special nature of a character by preceding it with a backslash. Because the backslash is also a special character in C++, we must use a second backslash inside a string literal to indicate to C++ that we want a backslash. Hence, we must write `\\.` to represent a regular expression that will match a period.

* Constructing a `regex` object and assigning a new regular expression to an existing `regex` can be time-consuming. To minimize this overhead, you should try to avoid creating more `regex` objects than needed. **In particular, if you use `regex` in a loop, construct it out of the loop.**

### The Match and Regex Iterator Types

We can get all the matches by using a `sregex_iterator`. The regex iterators are iterator adaptors that are bound to an input sequence and a `regex` object.

When we bind an `sregex-iterator` to a `string` and a `regex` object, the iterator is automatically positioned on the *first* match in the given `string`. When we increment the iterator, it calls the `regex_search` to find the next match in the input `string`

```C++
string pattern("[^c]ei");
pattern = "[[:alpha:]]*" + pattern + "[[:alpha:]]*";

regex r(pattern);       // construct a regex to find pattern
smatch results;         // define an object to hold the result of a search

string test_str = "receipt freind theif receive";

// find all matches
for (sregex_iterator iter(test_str.begin(), test_str.end(), r), end_iter;
    iter != end_iter;
    ++iter)
{
    cout << iter->str() << endl;
}
/* output:
freind
theif
*/
```

`smatch` and `ssub_match` let us see the context of a match. Function `prefix` and `suffix` return a `ssub_match` object

```C++
for (sregex_iterator it(file.begin(), file.end(), r), end_iter;
     it != end_iter; ++it)
{
    auto pos = it->prefix().length();   // size of the prefix
    // calculate the start index
    pos = pos > 40 ? pos - 40 : 0;      // we want up to 40 characters
    cout << it->prefix().str().substr(pos)
         << "\n found: " << it->str() << "\n"
         << it->suffix().str().substr(0, 40) // first part of the suffix
         << endl;
}
```

#### `smatch` Operations

* `m.str(n)`: The matched `string` for the `n`th subexpression. return the whole  matched sequence if n is *zero*.
* `m[n]`: returns `ssub_match` object corresponding to the `n`th subexpression

### Using Subexpressions

A pattern in a regular expression often contains one or more **subexpressions**. A subexpression is a part of the pattern that itself has meaning. Regular-expression grammars typically use the parentheses to denote the subexpression.

```C++
// r has two subexpression
regex r("([[:alnum:]]+)\\.(cpp|cxx|cc)$", regex::icase);
```

Our pattern now has two parenthesized subexpressions:

* `([[:alnum:]]+)`, which is a sequence of one or more characters
* `(cpp|cxx|cc)`, which is the file extension

We can also only print just the file name by changing the output statement:

```C++
if (regex_search(filename, results, r))
    cout << result.str(1) << endl;  // print the matched substring of first subexpression
```

#### Submatch Operations

* `matched`: A `public` `bool` data member that indicates whether this `ssub_match` was matched.
* `first`, `second`: `public` data member that are iterators to the start and one past the end of matching sequence.
* `length()`: The size of this match. Return 0 if `matched` is false
* `str()`: Return a `string` containing the matched portion of the input. Return an empty string if `matched` is false

### Using `regex_replace`

When we want to find and replace a regular expression in the input sequence, we call `regex_replace`. We compose a replacement string by including the characters we want, intermixed with *subexpressions* from the matched substring:

```C++
// using the second, fifth, seventh subexpression
string fmt = "$2.$5.$7";    // reformat numbers to ddd.ddd.dddd
```

We can use our regular-expression pattern and the replacement string as follows:

```C++
regex r(phone);
string number = "(908) 555-1800";
cout << regex_replace(number, r, fmt) << endl;
// output: 908.555.1800
```

#### Regular Expression Replacement Operations

* `m.format(dest, fmt, mfg)`: produces formatted ouput using the format string *fmt*, the match in `m`, and the optional `match_flag_type` flags in `mft`. write result to `dest` iterator.
* `m.format(fmt, mfg)`: same, but return the result as a string.
* `regex_replace(dest, seq, r, fmt, mft)`: Iterates through *seq*, using `regex_search` to find successive matches to regex `r`. Uses the format string `fmt` and optional `match_flag_type` flags in `mft` to produce its output.
* `regex_replace(seq, r, fmt, mft)`: same, but return the result as a string.

#### Using Format Flags

By default, `regex_replace` outputs its entire input sequence with all matches replaced. The parts that don't match the regular expression are output without change; the parts that do match are formatted as indicated by the given format string. We change this default behavior by specifying `format_no_copy` in the call to `regex_replace`:

```C++
// generate just the phone numbers
string fmt2 = "$2.$5.$7";

// tell regex_replace to copy only the text that it replaces
cout << regex_replace(s, r, fmt2, regex_constants::format_no_copy) << endl;
```

## Random Numbers

C++ programs should **not** use the library `rand` function. Instead, they should use the `default_random_engine` along with an appropriate distribution object.

### Random-Number Engines and Distribution

The random-number engines are function-object classes.

```C++
default_random_engine e;    // generate random unsigned integers
cout << e() << endl;
```

Random Number Engine Operations:

* `Engine e;`             Default ctor, uses the default seed for the engine type
* `Engine e(s);`          Uses the intgeral value `s` as the seed
* `e.seed(s);`            Reset the state of the engine using the seed `s`
* `e.min(); e.max();`     The smallest and largest numbers this generator will generate
* `Engine::result_type` The `unsigned` integral type this engine generates
* `e.discard(u);`         Advance the engine by `u` steps; `u` has type `unsigned long long`

#### Distribution Types and Engines

Like the engine types, the distribution types are also function-object classes. To get a number in a specified range, we use an object of a distribution type:

```C++
// uniformly distributed from 0 to 9 inclusive
uniform_int_distribution<unsigned> u(0, 9);
default_random_engine e;

cout << u(e) << endl;   // print a unifromly distributed value in the specified range
```

* When we refer to a **random-number generator**, we mean the combination of the `distribution` object with an `engine`
* A given random-number generator always produces the same sequence of numbers.
* A function with a local random-number generator should make that generator (both the engine and distribution objects) `static`. Otherwise, the function will generate the identical sequence on each call:

```C++
// error, it returns same sequence in every call
vector<unsigned> bad_randVec()
{
    default_random_engine e;
    uniform_int_distribution<unsigned> u(0, 9);
    vector<unsigned> ret;
    for (size_t i = 0; i < 100; ++i)
        ret.push_back(u(e));
    return ret;
}

// ok
vector<unsigned> good_randVec()
{
    static default_random_engine e;
    static uniform_int_distribution u(0, 9);

    // ... same to bad_randVec, genrates numbers and return
}
```

#### Seeding a Generator

A seed is a value that an engine can use to cause it to start generating numbers at a new point in its sequence.

### Other Kinds of Distribution

#### Generating Random Real Numbers

The most common, *but incorrect*, way to obtain a random floating-point from `rand` is to divide the result of `rand()` by `RAND_MAX`. This technique is incorrect because random integers usually have less precision than floating-point numbers, in which case there are some floating-point values that will *never* be produced as output.

With the new library facilities, we can easily obtain a floating-point random number:

```C++
default_random_engine e;

// uniformly distributed from 0 to 1 inclusive
uniform_real_distribution<duoble> u(0, 1);

cout << u(e) << endl;
```

#### Using the Distribution's Default Result Type

With one exception (`bernoulli_distribution`), the distribution types are templates that have a single template type parameter that represent the type of the numbers that the distribution generates.
Each distribution template has a default template argument. The distribution types that generate floating-point values generate `double` by default. Distribution that generate integral results use `int` as their default.

#### The `bernoulli_distribution` Class

`bernoulli_distribution` is an ordinary class, not a template. This distribution always return a `bool` value. It returns `true` with a given probability. By default that probability is 0.5;

## The IO Library Revisited

### Formatted Input and Output

The library defines a set of **manipulators** that modify the format state of a stream.

```C++
cout << true << " " << false << endl;               // 1 0
cout << boolalpha << true << " " << false << endl;  // true false

cout << "default: " << 20 << " " << 1024 << endl;
cout << "octal: " << oct << 20 << " " << 1024 << endl;
cout << "hex: " << hex << 20 << " " << 1024 << endl;
cout << "decimal: " << dec << 20 << " " << 1024 << endl;
/* output:
default: 20 1024
octal: 24 2000
hex: 14 400
decimal: 20 1024
*/

cout << showbase;   // show the base when printing integral values
cout << "default: " << 20 << " " << 1024 << endl;
cout << "octal: " << oct << 20 << " " << 1024 << endl;
cout << "hex: " << hex << 20 << " " << 1024 << endl;
cout << "decimal: " << dec << 20 << " " << 1024 << endl;
cout << noshowbase;
/* output:
default: 20 1024
octal: 024 02000
hex: 0x14 0x400
decimal: 20 1024
*/
```

* `hex`, `oct` and `dec` affect only integral operands; the representation of floating-point values is unaffected.
* By default, hexadecimal values are printed in lowercase with a lowercase x. We can display the *X* and the hex digits *a-f* as uppercase by applying the `uppercase` manipulator

```C++
cout << uppercase << showbase << hex
     << "printed in hexadecimal: " << 10 << " " << 1024
     << nouppercase << noshowbase << dec << endl;
// output:
// printed in hexadecimal: 0XA 0X400
```

### Controlling the Format of Floating-Point Values

We can control three aspect of floating-point output:

* How many digits of precision are printed
* Whether the number is printed in hexadecimal, fixed decimal, or scientific notation.
* Whether a decimal point is printed for floating-point values that are whole numbers.

#### Specifying How Much Precision to Print

By default, precision controls the total nubmer of digits that are printed. **When printed, floating-point values are rounded, not truncated, to current precision.**

```C++
// cout.precision reports the current precision value
cout << "Precision: " << cout.precision()
     << ", Value: "   << sqrt(2.0) << endl;

// cout.precision(12) asks that 12 digits of precision be printed
cout.precision(12);
cout << "Precision: " << cout.precision()
     << ", Value: "   << sqrt(2.0) << endl;

// alternative way to set precision usint the setprecision manipulator
cout << setprecision(3) << "Precision: " << cout.precision()
     << ", Value: "     << sqrt(2.) << endl;

/* output
Precision: 6, Value: 1.41421
Precision: 12, Value: 1.41421356237
Precision: 3, Value: 1.41
*/
```

#### Specifying the Notation of Floating-Point Numbers

Unless you need to control the presentation of a floating-point number (e.g., to print data in columns or to print data that represents money or a percentage), it is usually best to let the library choose the notation.

* The `scientific` manipulator  changes the stream to use scientific notation
* The `fixed` manipulator changes the stream to use fixed decimal
* The `hexfloat` force the floating-point values to use hexadecimal format
* The `defaultfloat` returns the stream to its default state in which it chooses a notation based on the value being printed.

After executing `scientific`, `fixed`, or `hexfloat`, the precision value controls the number of digits after the decimal point. By default, precisioin specifies the total number of digits--both before and **after the decimal point.**

#### Printing the Decimal Point

The `showpoint` manipulator forces the decimal point to be printed:

```C++
cout << 10.0 << endl;           // print 10
cout << showpoint << 10.0
     << noshowpoint << endl;    // print 10.0000
```

#### Padding the Output

* `setw` specifies the minimum space for the *next* numeric or string value
* `left` left-justifies the output
* `right`right-justifies the output, which is default behavior.
* `internal` controls placement of the sign on negative values, `internal` left-justifies the sign and right-justifies the value, padding any intervening space with blank
* `setfill` lets use specify an alternative character to use to pad the output

### Unformatted Input/Output Operations

#### Single-Byte Operations

```C++
char ch;
while (cin.get(ch))
    cout.put(ch)
```

#### Putting Back onto an Input Stream

Sometimes we need to read a character in order to know we aren't ready for it. In such cases, we'd like to put the character back onto the stream.

* `peek` returns a copy of the next character on the input stream but does not change the stream.
* `unget` backs up the input stream so that whatever value was last returned is still on the stream.
* `putback` is a more specialized version of `unget`: It returns the last value read from the stream but takes an argument that must be the same as the one that was last read

We are not guaranteed to be albe to call `putback` or `unget` without an intervening read operation.

#### Multi-Byte Operations

* `is.get(sink, size, delim)`
  + Reads *up* to `size` bytes from `is` and stores them in the character array beginning at the address pointed to by `sink`. Reads until encountering the `delim` character or until it has read `size` bytes or encounters end-of-fild. **If `delim` is present, it is left on the input stream and not read into `sink`**
* `is.getline(sink, size, delim)`
  + Same behavior as the three-argument version of `get` but **reads and discards `delim`**
* `is.read(sink, size)`
  + Reads up to `size` bytes into the character array `sink`. Return `is`
* `is.gcount()`
  + Returns number of bytes read from the stream `is` by the last call to an unformatted read operation
* `os.write(source, size)`
  + write `size` bytes from the character array `source` to os. Returns os
* `is.ignore(size, delim)`
  + Reads and ignores at most `size` characters up to and **including `delim`**.

#### Determinging How Many Characters Were Read

It is essential to call `gcount` before any intervening unformatted input operation. In particular, the single-character operations that put characters back on the stream are also unformatted input operations. If `peek`, `unget`, or `putback` are called before calling `gcont`, then the return value will be 0.

### Random Access to a Stream

We can reposition the stream so that it skips around, reading first the last line, then the first, and so on.

> Random IO is an inherently system-dependent. To understand how to use these features, you must consult your system's documentation

On most systems, the streams bound to `cin`, `cout`, `cerr` and `clog`do *not* support random access.

#### Seek and Tell Functions

The library actually defines two pairs of *seek* and *tell* functions.

* `tellg()`, `tellp()` Return teh current position of the marker in an input stream (`tellg`) or an output stream (`tellp`)
* `seekg(pos)`, `seekp(pos)` Reposition the marker in an input or output stream to the given absolute address in the stream. `pos` is usually a value returned by a previous call to the corresponding `tellg` or `tellp` function
* `seekg(off, from)`, `seekp(off, from)` Reposition the marker for an input or output stream `off` characters ahead or behind `from`. `from` can be one of
  + `beg`, seek relative to the begining of the stream
  + `cur`, seek relative to the current position of stream
  + `end`, seek relative to the end of the stream

#### There Is Only One Marker

There is *not* a distinct read marker and write marker. The library maps both the `g` and the `p` positions to the single marker.

### Repositioning the Marker

```C++
// set the marker to a fixed position
seekg(new_position);
seekp(new_position);

// offset some distance ahead of or behind the given starging point
seekg(offset, from);
seekp(offset, from);
```

The arguments, `new_position` and `offset`, have machine-dependent types named `pos_type` and `off_type`, respectively. A value of type `off_type` can be positive or negative; we can `seek` forward or backward in the file.

#### Accessing the Marker

```C++
ostringstream writeStr;
ostringstream::pos_type mark = writeStr.tellp();

//...

if (cancelEntry)
    writeStr.seekp(mark);   // return to the remembered position
```