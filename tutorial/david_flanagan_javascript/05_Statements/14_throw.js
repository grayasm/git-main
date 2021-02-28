/* Cap.5 Statements
   5.6.5 throw

   $ node 14_throw.js

   An exception is a signal that indicates that some sort of exception condition
   or error has occurred.

   throw expression;
*/


function factorial(x) {

    if (x < 0)
        throw new Error("x must be positive");

    for (var f = 1; x > 1; f *= x, x--) /*empty*/;

    return f;
}

console.log("factorial(3)=", factorial(3));
//factorial(3)= 6

console.log("factorial(-1)=", factorial(-1));
/*
throw new Error("x must be positive");
Error: x must be positive
*/
