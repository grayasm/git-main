===============================================================================
                   Cap.3 Types, Values and Variables
===============================================================================
  1) Primitive types: undefined, null, booleans, numbers and  strings
     Object types   : objects,  arrays,   functions

     Numbers
     =======
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


     Strings
     =======
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

     Booleans
     ========
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

     Objects
     =======
 15) Node.js global object is "Global"
     Chrome/FF/IE browsers global object is "Window"
     The global object has functions and properties.

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

 17) Mutable objects vs immutable primitives
     Immutable primitives: undefined, null, booleans, numbers and strings.
     Mutable objects:      objects, arrays and functions.

     var s = "hello";  // Start with some lowercase text
     s.toUpperCase();  // Returns "HELLO", but doens't alter s
     s;                // => "hello": the original string has not changed

     Cannot mutate a primitive, but only change its value by assignment.
     Primitive values are compared by value.
     Objects are compared by reference.

 18) Primitive to object conversion
     It can happen automatically:
     var a = 10 + "objects";   // a string value="10 objects"

     It can happen explicitly by calling:
       new String(..)
       new Number(..)
       new Boolean(..)

     Certain idioms have emerged:
       x + ""   same as String(x)
       +x       same as Number(x)
       x-0      same as Number(x)
       !!x      same as Boolean(x); note double !

 19) Object to primitive conversion
     Object to boolean:
       all objects including arrays and functions convert to true
       new Boolean(false) converts to true.

     Object to string:
       all objects inherit 2 methods: toString() and valueOf()
       if object implements toString() : done
       if object implenebts valueOf() converts the value to string : done
       otherwise throws TypeError

     Object to number:
       if object implements valueOf() : done
       if object implements toString() converts teh string to number : done
       otherwise throws TypeError


     Variables
     =========
 20) Declare variable using var:
     var a;
     var b, c;

     Combine declaration with initialization:
     var m = "helo";
     var i = 0, j = 0, k = 0;

     Declare a variable as part of for loop:
     for(var i = 0; i < 3; i++) { }

     Declare a variable more than once with var statement:
     var i = 0;
     var i = -5;

 21) Scope
     By 'hoisting' a variable is present in a function before its declaration.

     var s = "global"
     function test() {
         // s is 'undefined'    <-- this is particular to JavaScript.
         var s = "local"
         // s is 'local'
     }
     // s is 'global' again

 22) Variable as Properties
     If a variable is declared with 'var' it cannot be deleted with 'delete'
     If a value is assigned to a undeclared variable, the new global variable
     can be deleted with operator 'delete'

     var i = 0;
     j = 0;

     delete i;   // false; does not delete global property 'i'
     delete j;   // true; global property 'j' is deleted.
