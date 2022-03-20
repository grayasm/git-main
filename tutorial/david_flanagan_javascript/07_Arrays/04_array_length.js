/* Cap.7 Arrays
   7.4 Array Length

   $ node 04_array_length.js


   Every array has a length property, and it is this property that makes arrays
   different from regular JavaScript objects.
*/


[].length;                // => 0: the array has no elements
['a', 'b', 'c'].length;   // => 3: highest index is 2, length is 3


// Side effect of setting an array's length:

a = [1,2,3,4,5];          // Start with a 5-element array.
a.length = 3;             // a is now [1,2,3]
a.length = 0;             // Delete all elements. a is [].
a.length = 5;             // Length is 5, but no elements, like new Array(5)


// In ECMAScript 5, you can make the length property of an array read-only with
// Object.defineProperty()

a = [1,2,3];                              // Start with a 3-element array.
Object.defineProperty(a, "length",        // Make the length property
                      {writable: false}); // readonly.
a.length = 0;                             // a is unchanged.
