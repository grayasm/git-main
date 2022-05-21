/* Cap.7 Arrays
   7.5 Adding and Deleting Array Elements

   $ node 05_array_add_delete.js
*/

a = [];                   // Start with an empty array
a[0] = "zero";            // and add elements to it.
a[1] = "one";


// Using push() method:
a = [];                   // Start with an empty array.
a.push("zero");           // Add a value at the end. a=["zero"]
a.push("one", "two");     // Add two more values. a=["zero", "one", "two"]


// You can delete array elements with the delete operator,
// just as you can delete object properties:

a = [1,2,3];
delete a[1];               // a now has no element at index 1
1 in a;                   // => false: no array index 1 is defined
a.length;                 // => 3: delete does not affect array length


// If you delete an element from an array, the array becomes sparse.

// You can delete elements from the end of an array simply by setting
// the length property to the new desired length.

// There are other methods that help manipulate the elements of an array:
// pop(), push(), shift(), unshift(), delete(), splice().
