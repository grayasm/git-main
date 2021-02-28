/* Cap.5 Statements
   5.6.4 return

   $ node 13_return.js

   return expression;

   > may appear only within the body of a function
   > a function without a return evaluates to undefined
*/

function square(x)
{
    return x * x;
}
console.log("square(2)=", square(2));
// square(2)= 4
