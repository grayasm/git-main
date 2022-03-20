/* Cap.7 Arrays
   7.8.3 sort()

   $ node 10_method_sort.js

   Array.sort() sorts the elements in place.
   When called with no arguments it sorts in alphabetical order, temporarily
   converting them to strings to perform the comparison if necessary.
   Undefined elements are sorted at the end of the array.
*/


var a = new Array("banana", "cherry", "apple");
a.sort();
var s = a.join(", ");  // s == "apple, banana, cherry"


// You can pass a comparison function as argument to sort().
var a = [33, 4, 1111, 222];

a.sort();      // Alphabetical order: 1111, 222, 33, 4
a.sort(function(a,b) { return a-b; }); // => 4, 33, 222, 1111
a.sort(function(a,b) { return b-a; }); // => Reverse numerical order



// Another example of sorting array items.
a = ['ant', 'Bug', 'cat', 'Dog'];
a.sort();               // case-sensitive sort: ['Bug','Dog','ant','cat']
a.sort(function(s,t) {
    var a = s.toLowerCase();
    var b = t.toLowerCase();
    if (a < b) return -1;
    if (a > b) return 1;
    return 0;
});                    // case-insensitive sort: ['ant','Bug','cat','Dog']
