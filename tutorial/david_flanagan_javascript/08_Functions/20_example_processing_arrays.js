/* Cap.8 Functions
   8.8.1 Processing Arrays with Functions

   $ node 20_example_processing_arrays.js

   Calculate the mean and standard deviation in a concise functional style
   using map() and reduce().
*/

var sum = function(x,y) { return x+y; }
var square = function(x) { return x*x; }

var data = [1,1,3,5,5]
var mean = data.reduce(sum) / data.length;
var deviations = data.map(function(x) { return x-mean; });

var stddev = Math.sqrt(deviations.map(square).reduce(sum)/(data.length-1));

console.log(mean);         // => 3
console.log(deviations);   // => -2,-2,0,2,2
console.log(stddev);       // => 2
