/* Cap.7 Arrays
   7.8.7 push() and pop()

   $ node 14_method_push_pop.js

   push() appends one or more new elements to the end of the array and returns
          the new length of the array.
   pop()  deletes the last element of the array, decrements the array length,
          and returns the value that it removed.
*/


var stack = [];    // stack: []
stack.push(1,2);   // stack: [1,2]     Returns 2
stack.pop();       // stack: [1]       Returns 2
stack.push(3);     // stack: [1,3]     Returns 2
stack.pop();       // stack: [1]       Returns 3
stack.push([4,5]); // stack: [1,[4,5]] Returns 2
stack.pop()        // stack: [1]       Returns [4,5]
stack.pop()        // stack: []        Returns 1
