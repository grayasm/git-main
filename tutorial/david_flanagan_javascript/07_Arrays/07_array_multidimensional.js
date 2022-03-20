/* Cap.7 Arrays
   7.7 Multidimensional Arrays

   $ node 07_array_multidimensional.js

   JavaScript does not support multidimensional array, but can approximate
   them with arrays of arrays.

   Use operator [] twice.
*/

// Create a multidimensional array
var table = new Array(10);           // 10 rows of the table
for (var i = 0; i < table.length; i++)
    table[i] = new Array(10);        // Each row has 10 columns

// Initialize the array
for (var row = 0; row < table.length; row++){
    for (var col = 0; col < table[row].length; col++){
        table[row][col] = row * col;
    }
}

// Use the multidimensional array to compute 5 * 7
var product = table[5][7]; // 35
console.log('table[5][7] = ' + product);
