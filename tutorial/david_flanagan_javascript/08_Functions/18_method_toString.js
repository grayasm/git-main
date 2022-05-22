/* Cap.8
   8.7.5 The toString() Method

   $ node 18_method_toString.js

   Like all JavaScript objects, functions have a toString() method.
*/


function sum(a, b) {
  return a + b;
}

console.log(sum.toString());
// expected output: "function sum(a, b) {
//                     return a + b;
//                   }"
