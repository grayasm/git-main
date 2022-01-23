/* Cap.7 Arrays
   7.2 Reading and Writing Array Elements

   $ node 02_array_read_write.js


   You access an element of an array using the [] operator.
*/


var a = ["world"];       // start with a one-element array
var value = a[0];        // read element 0
a[1] = 3.14;             // write element 1
i = 2;
a[i] = 3;                // write element 2
a[i + 1] = "hello";      // write element 3
a[a[i]] = a[0];          // read elements 0 and 2, write element 3


// There is nothing special about the conversion of the index from a number
// to a string: you can do that with regular objects, too:
o = {};                  // Create a plain object
o[1] = "one";            // Index it with an integer


// The length property is updated as we change the array.
a.length;                // => 4


// It is helpful to clearly distinguish an array index from an object property name.
// All indexes are property names, but only property names that are integers
// between 0 and 2^32-1 are indexes.

a[-1.23] = true;      // This creates a property named "-1.23"
a["1000"] = 0;        // This the 1001st element of the array
a[1.000];             // Array index 1. Same as a[1]


// When you try to query a nonexistent property of any object, you don’t get
// an error, you simply get undefined . This is just as true for arrays as
// it is for objects:
a = [true, false];    // This array has elements at indexes 0 and 1
a[2];                 // => undefined. No element at this index.
a[-1];                // => undefined. No property with this name.
