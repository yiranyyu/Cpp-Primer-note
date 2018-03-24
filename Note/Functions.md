# Functions

## Function Basic

## Argument Passing

## Return Types and the return Statement

## Overloaded Functions

## Function Matching

### Argument Type Conversions

In order to determine the best match, the compiler ranks the conversions that could be used to conver each argument to the type of its corresponding parameter. Conversions are ranked as follows:

1. An excat match. An exact match happens when:

* The argument and parmeters types are identical
* The argument is converted from an array or function type to the corresponding pointer type.
* A top-level `const` is added to or discard from the argument

2. Match through a `const` conversion
3. Match through a promotion
4. Match through an arithmetic or pointer conversion
5. Match through a class-type conversion.

## Pointer to Functions