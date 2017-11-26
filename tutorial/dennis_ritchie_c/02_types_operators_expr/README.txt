.
                      Cap.2 Types, Operators and Expressions
                      pag.35-54

  1. the underscore "_" counts as a letter
  2. function names and external variables may have less then 31 characters
     because are used by assemblers and loaders over which the language has no
     control
  3. C basic types are: char, int, float, double
  4. qualifiers may be applied to these basic types: short int, long int
  5. qualifiers signed, unsigned may be applied to char or any integer
  6. string constants can be concatenated at compile time: "hello, " "world"
  7. the internal representation of a string has a null character '\0' at the
     end, so the physical storage required is one more than the number of
     characters written between the quotes
  7. external and static variables are initialized to zero by default.
  8. automatic variables for which there is no explicit initializer have
     undefined (garbage) values
  9. the automatic conversion promotes a "narrower" operand into a "wider"
     operand without losing information, such as converting an integer to a
     floating point in an expression like: f + i
 10. the implicit arithmetic conversion promotes the "lower" type to the "higher"
     type before the operation proceeds
 11. binary ^ xor with 1 toggles the bit:  1001 ^ 1111 = 0110
 12. unary negation ~ flips all bits: ~(~0 << 2) << 1  = 0110
