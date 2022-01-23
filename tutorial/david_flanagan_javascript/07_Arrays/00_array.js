/* Cap.7 Arrays

   $ node 00_array.js

   An array is an ordered collection of values. Each value is called an
   element, and each element has a numeric position in the array, known as
   its index. JavaScript arrays are untyped: an array element may be of any
   type, and different elements of the same array may be of different types.
   Array elements may even be objects or other arrays, which allows you to
   create complex data structures, such as arrays of objects and arrays of
   arrays. JavaScript arrays are zero-based and use 32-bit indexes: the index
   of the first element is 0, and the highest possible index is 4294967294 (2^32),
   for a maximum array size of 4,294,967,295 elements.

   JavaScript arrays are dynamic: they grow or shrink as needed and there is
   no need to declare a fixed size for the array when you create it or to
   reallocate it when the size changes. JavaScript arrays may be sparse:
   the elements need not have contiguous indexes and there may be gaps.
   Every JavaScript array has a length property. For nonsparse arrays,
   this property specifies the number of elements in the array.
   For sparse arrays, length is larger than the index of all elements.
*/
