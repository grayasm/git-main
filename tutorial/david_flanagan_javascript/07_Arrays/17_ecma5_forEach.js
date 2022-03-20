/* Cap.7 Arrays
   7.9.1 forEach()

   $ node 17_ecma5_forEach.js

   Array.forEach() iterates through an array, invoking a function you specify
   for each element.
*/


var data = [1,2,3,4,5];
var sum = 0;
data.forEach(function(value) { sum += value; });  // Compute the sum
sum;                                              // => 15

data.forEach(function(v, i, a) {a[i] = v + 1;});  // Increment each element
data;                                             // => [2,3,4,5,6]


// Provide a way to terminate iteration before all elements have been passed
// to the function.
function foreach(a,f,t) {
    try
    {
        a.forEach(f,t);
    }
    catch(e)
    {
        if (e === foreach.break) return
        else throw e;
    }
}
foreach.break = new Error("Stop Iteration");
