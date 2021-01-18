/* Cap.4 Expressions and Operators
   4.12.1 eval()

   $ node 21_eval.js

   eval() function expects one argument:
   - if you pass any value other than a string, it simply returns that value
   - if you pass a string, it attempts to parse the string as JavaScript code
   - if it cannot parse the string, then it throws SyntaxError
   - if it parses the string, then returns the value of the last expression
   - if the last expression has no value, then returns 'undefined'
*/

console.log(  eval("var x;")  );  // undefined
console.log(  eval("x = 1;")  );  // 1
console.log('x=', x);             // x=1 : x is now defined

eval("var y = 3");                // declare a new variable y
console.log('y=', y);             // y=3

eval("function inc(x){return x+1;}"); // declare a function inc(x)
var z = inc(y);
console.log('z=', z);             // z=4
