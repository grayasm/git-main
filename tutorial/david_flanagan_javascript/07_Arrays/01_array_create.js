/* Cap.7 Arrays
   7.1 Creating Arrays

   $ node 01_array_create.js


   The easiest way to create an array is with an array literal, which is
   simply a comma-separated list of array elements within square brackets.

   Another way to create an array is with the Array() constructor.
*/


var empty = [];                         // an array with no elements
var primes = [2, 3, 5, 7, 11];          // an array with 5 numeric elements
var misc = [ 1.1, true, "a", ];         // 3 elements of various types


// The values in an array literal need not be constants; they may be
// arbitrary expressions
var base = 1024;
var table = [base, base+1, base+2, base+3];

// Array literals can contain object literals or other array literals:
var b = [[1, {x:1, y:2}], [2, {x:3, y:4}]];

// If you omit a value from an array literal, the omitted element is given
// the value undefined :
var count = [1,,3]; // An array with 3 elements, the middle one undefined.
var undefs = [,,];  // An array with 2 elements, both undefined.


// Another way to create an array is with the Array() constructor (3 ways)

var a = new Array();                                  // creates an empty array
var a = new Array(10);                                // specifies the length
var a = new Array(5, 4, 3, 2, 1, "testing, testing"); // specify the elements
