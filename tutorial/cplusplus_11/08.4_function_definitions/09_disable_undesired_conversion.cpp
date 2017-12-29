/*  http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2007/n2210.html

    Disabling Undesired Conversions
    Removing dangerous conversions is as important as removing undesired
    language defaults.
*/

#include <stdio.h>

void write(double value);          // actual function
void write(int value) = delete;    // avoid invoking with an int argument

template<typename T>
void write(T value) = delete;      // avoid invoking with all other types


/* Of considerable note is the interaction of explicit constructors
   and explicit conversion operators with deleted definitions.
   The short answer is that the two facilities are orthogonal, explicit controls
   the set of functions considered and delete comments on the final choice.
*/

struct type {
    type(long long) { printf("type(long long)\n"); }
    explicit type(long) = delete;
};
extern void function(type);

main()
{
    write(42.0);  // okay
    //  write(42) - ERROR: will not compile
    //  function(type(42));  - ERROR: 42 promotes to long
    function(42); // okay type(long long);
}

void write(double) { printf("write(double)\n"); }
void function(type) { printf("function(type)\n"); }

/*
  write(double)
  type(long long)
  function(type)
*/
