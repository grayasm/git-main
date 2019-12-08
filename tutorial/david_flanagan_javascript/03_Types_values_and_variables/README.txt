===============================================================================
                   Cap.3 Types, Values and Variables
===============================================================================
  1) Primitive types: numbers,  strings,  booleans
     Object types   : objects,  arrays,   functions
------------------------------------------------------------------------numbers
  2) All numbers are stored as 64 bit floating-point in IEEE 754 standard
     minim= +/-5 x 10^-324
     maxim= +/-1.7976931348623157 x 10^308
  3) For integers:
     minim= -2^53
     maxim= +2^53
  4) Hexadecimal (base-16) format 0x or 0X  = 0xff
  5) Octal (base-8) format non-standard 0.. = 0377
  6) Floating point literals = [digits][.digits][(E|e)]digits]
     3.14
     2345.789
     .33333
     6.02e23
     1.4738223E-32
  7) Math class can help with arithmetic operations= Math.sqrt(3);
  8) No errors for overflow, underflow, or divizion by zero. (see Infinity, NaN)
  9) JavaScript is affected by floating-point rounding errors just like C/C++.
     (.3 - .2) == (.2 - .1); // is false
------------------------------------------------------------------------strings
 10) var s = 'name="myform"';
     var s = "Wouldn't you prefer O'Reilly's book?";
     var s = "two\nlines";
     var s = "one\
              long\
              line";
 11) Escape sequence uses \
     var s = 'You\'re right, it can\'t be a quote';
 12) Working with strings
     var s = "hello, " + "world";
     var h = s[0];
     var d = s[s.length - 1];
-----------------------------------------------------------------------booleans
 13) Any JavaScript can be converted to a boolean value.
 14) The folowing values convert to false
     undefined
     null
     0
     -0
     NaN
     ""
     null ==  undefined;  // is true
     null === undefined;  // is false, strict comparison
------------------------------------------------------------------------objects
 15) The global object has functions and properties.
     var a = isFinite(200);         // method of the global object "this"
     var a = this.isFinite(200);
     var p = this.Infinity;         // property
 16) Wrapper objects convert behind the scene the primitive types into objects.
     var s = "test";
     var n = 10;
     var b = true;
     s.length();       // =>  4:    s is wrapped with: new String("test")
     n.toString();     // => "10":  n is wrapped with: new Number(10);
     b.toString();     // => "true: b is wrapped with: new Boolean(true);
 17) 
