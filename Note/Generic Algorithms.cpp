#include <iostream>
#include <iterator>
#include <vector>
using namespace std;
namespace note{
void f(){

// note
istream_iterator<int> int_iter(cin);
decltype(int_iter) eof;// default init 
vector<int> ints;

while (int_iter != eof) // same as while(cin >> $val$)
    ints.push_back(*int_iter++);

// more useful
vector<int> vec(int_iter, eof);

//                                  iter              end()
//                                   ↓                 ↓
vector<char> word = {'l', 'e', 't', 't', 'e', 'r' /*, end*/ };
//                              ↑              ↑  
//                            r_iter         rbegin()

auto r_iter = word.rbegin() + 3;
auto iter = r_iter.base();
//   [r_begin(), r_iter) == [iter, end())
// i.e. [r_begin(), r_iter] == [r_iter.base(), end()]  
}
}