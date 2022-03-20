/* Cap.7 Arrays
   7.3 Sparse Arrays

   $ node 03_array_sparse.js


   A sparse array is one in which the elements do not have contiguous indexes
   starting at 0.
*/


a = new Array(5);     // No elements, but a.length is 5
a = [];               // Create an array with no elements and length = 0.
a[1000] = 0;          // Assignment adds one element but sets length to 1001.


/*  Note that when you omit value in an array literal, you are not creating
    a sparse array. The omitted element exists in the array and has the value
    undefined . This is subtly different than array elements that do not exist
    at all. You can detect the difference between these two cases with
    the in operator:
*/

var a1 = [,,,];           // This array is [undefined, undefined, undefined]
var a2 = new Array(3);    // This array has no values at all.
0 in a1;                  // => true: a1 has an element with index 0
0 in a2;                  // => false: a2 has no element with index 0
