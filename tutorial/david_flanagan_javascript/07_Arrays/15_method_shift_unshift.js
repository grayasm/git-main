/* Cap.7 Arrays
   7.8.8 unshift() and shift()

   $ node 15_method_shift_unshift.js

   unshift() adds one or more elements to the beginning of the array and returns
             the new length of the array.
   shift()   removes and returns the first element of the array, shifting all
             subsequent elements down one place.
*/

var a = [];         // a=[]
a.unshift(1);       // a=[1]          Returns 1
a.unshift(22);      // a=[22,1]       Returns 2
a.shift();          // a=[1]          Returns 22
a.unshift(3,[4,5]); // a=[3,[4,5],1]  Returns 3
a.shift();          // a=[[4,5],1]    Returns 3
a.shift();          // a=[1]          Returns [4,5]
a.shift();          // a=[]           Returns 1
