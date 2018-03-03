#include <iostream>
using namespace std;
int note_8()
{
    auto p_cout = cin.tie();
    bool same = (p_cout == &cout); // true

    // tie cin with cerr by transfer a pointer to the stream and return the old tied stream
    auto p_cout_1 = cin.tie(&cerr);
    cin.tie(p_cout_1);// retie cin with cout(normal state)

}