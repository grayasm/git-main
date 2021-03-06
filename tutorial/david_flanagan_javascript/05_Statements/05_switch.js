/* Cap.5 Statements
   5.4.3 switch

   $ node 05_switch.js

   The switch statement has the following syntax:

   switch (expression) {
       statements
   }
*/

var n = 10;

switch(n) {
case 1:
    // Execute code block #1
    break;

case 2:
    // Execute code block #2
    break;

case 3:
    // Execute code block #3
    break;

default:
    // Execute code block #4
    break;
}


// You can let the execution "fall through" or use return to break out.
function convert(x) {
    switch(typeof(x)) {

    case 'number':
        return x.toString(16);

    case 'string':
        return '"' + x + '"';

    default:
        return String(x);
    }
}

console.log(  convert(255)  );    // ff
console.log(  convert('255'));    // "255"
