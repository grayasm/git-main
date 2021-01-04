/* Cap.3 Types, Values and Variables
   3.7 Immutable Primitive Values and Mutable Object References

   $ node 15_immutable_vs_mutable.js

   Immutable primitives: undefined, null, booleans, numbers, strings.
   Mutable Objects:      objects, arrays, functions.

   Immutable primitive values:
   1. cannot 'mutate' a primitive value; only change its value by assignment '='
   2. compared by value

   Mutable object references:
   1. can 'mutate' which means their properties can change
   2. compared by reference
*/


// Primitives do not 'mutate' (change in place).
var s1 = "test";
var s2 = "test";
console.log(s1 == s2);            // true: compared by value
console.log(s1 === s2);           // true: compared by value

console.log(s1.toUpperCase());    // "TEST"  <-- copy of s1
console.log(s1);                  // "test"  <-- s1 unchanged


// Objects are mutable (change in place)
var o1 = { x:1 };                 // Start with an object.
o1.x = 2;                         // Mutate it by changing the value of a property.
o1.y = 3;                         // Mutate it again by adding a new property.
console.log(o1);                  // { x:2, y: 3 }


// Arrays are objects
var a1  = [1,2,3];                // Arrays are also mutable
a1[0] = 0;                        // Change the value of an array element
a1[3] = 4;                        // Add a new array element
console.log(a1);                  // [ 0, 2, 3, 4 ]


// Objects compare (FALSE)
var o2 = {x:1}, p2 = {x:1};
console.log(o2 == p2);            // false: compared by reference
console.log(o2 === p2);           // false: compared by reference

var a2 = [], b2 = [];
console.log(a2 == b2);            // false: compared by reference
console.log(a2 === b2);           // false: compared by reference


// Objects compare (TRUE)
var a3 = [];
var b3 = a3;
b3[0] = 1;
console.log('a3=', a3);           // a3= [ 1 ]
console.log(a3 == b3);            // true: refer to the same underlying object
console.log(a3 === b3);           // true: refer to the same underlying object


// Copy an object by copying its values.
var a4 = ['a', 'b', 'c'];                        // Array we want to copy
var b4 = [];                                     // Array we copy into
for (var i = 0; i < a4.length; i++) {
    b4[i] = a4[i];                               // Copy an element of a into b
}


// Compare objects or arrays by comparing their values.
function equalArrays(a,b) {
    if (a.length != b.length)
        return false;
    for (var i = 0; i < a.length; i++)
        if (a[i] != b[i])
            return false;
    return true;
}

console.log('a4=', a4);                                 // a4= [ 'a', 'b', 'c' ]
console.log('b4=', b4);                                 // b4= [ 'a', 'b', 'c' ]
console.log('equalArray(a4,b4)=', equalArrays(a4,b4));  // true
