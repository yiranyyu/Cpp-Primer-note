#include "stdafx.h"

namespace ty
{
typedef double D_float;
// same to normal declaration, using type modifiers for compound type built from base type
typedef D_float *pD_float, D_float_alias;

// New standard
using L_int = long;
using LL_int = long long;

// auto type specifier
const int ci = 0;
auto a_i = ci;   // a_i is int obj(ignore top-level const)
auto *p_i = &ci; // p_i is pointer to const(inherit low-level const)

// decltype
const int &rci = ci;
decltype(rci) x = ci;   // x is reference of const int.( refrence no seen as the obj it refers)
}