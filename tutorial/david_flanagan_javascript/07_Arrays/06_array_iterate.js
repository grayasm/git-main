/* Cap.7 Arrays
   7.6 Iterating Arrays

   $ node 06_array_iterate.js

   Use 'for' loop.
   Use 'for in' loop, for sparse arrays.
   Use forEach() method.
*/

var o = {
    1 : "one",
    2 : "two"
}
var keys = Object.keys(o);   // Get an array of property names for object o
var values = [];             // Store matching property values in this array
for (var i = 0; i < keys.length; i++) {  // For each index in the array
    var key = keys[i];                   // Get the key at that index, e.g. 1,2
    values[i] = o[key];                  // Store the value in the values array
    // keys=[1, 2]
    // values=["one", "two"]
    console.log("key:" + key + ", value=" + values[i]);
};

// Looking up the array length only once may speed up the looping.
for(var i = 0, len = keys.length; i < len; i++){
    // loop body remains the same
}

// Exclude null, undefined and nonexistent elements
var a = [1, 2, 3, 4, 5, null, null, 8];
delete a[1]; // '2'
for (var i = 0; i < a.length; i++) {

    if (!a[i]) continue;   // Skip null, undefined, and nonexistent elements
    if (a[i] === undefined) continue; // Skip undefined and nonexistent elements
    if (!(i in a)) continue;          // Skip nonexistent elements

    // loop body here
    console.log('a[' + i + ']=' + a[i]);  // shows [1,3,4,5,8]
}


// Iterate sparse arrays.
for (var i in a) {
    var value = a[i];
    console.log('sparse a[' + i + ']=' + a[i]);  // shows [1,3,4,5,null,null,8]
}


// Iterates sparse arrays and skip the inherited properties.
for (var i in a) {
    if (!a.hasOwnProperty(i)) continue;  // Skip inherited properties
    // loop body here
    console.log('a[' + i + ']=' + a[i]);  // shows [1,3,4,5,null,null,8]
}


// ECMAScript 5 defines a number of new methods for iterating array elements.
var a = [1,2,3,4,5];
var sumOfSquares = 0;
a.forEach(function(x) { sumOfSquares += x * x; });

console.log('sumOfSquares=' + sumOfSquares); // 55
