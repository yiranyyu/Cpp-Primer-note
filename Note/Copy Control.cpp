#include <string>
namespace note{ void CopyControl(){
using namespace std;

string dots(10, '.');               // direct initialization
string s(dots);                     // direct initialization
string s2 = dots;                   // copy initialization
string null_book = "9-999-99999-9"; // copy initialization
string nines = string(100, '9');    // copy initialization


class CopyControlClass {
    void f()const &;// ok
    void f()&;      // ok
    
    // syntax error, reference quilifier should follow const qualifier
/*  void f() & const; */
};
}}