/* Cap.8
   8.4 Functions As Values

   $ node 10_function_as_value.js

   In JavaScript functions can be assigned to variables, stored in properties
   of objects or the elements of arrays, passed as arguments to functions
   and so on.
*/

// Example using functions as data:
function add(x,y) { return x+y; }
function subtract(x,y) { return x-y; }
function multiply(x,y) { return x*y; }
function divide(x,y) { return x/y; }

function operate(operator, operand1, operand2){
    return operator(operand1, operand2);
}

var i = operate(add, operate(add, 2, 3), operate(multiply, 4, 5)); // => i=25



// Example using functions as object literal:
var operators = {
    add:        function(x,y){ return x+y; },
    subtract:   function(x,y){ return x-y; },
    multiply:   function(x,y){ return x*y; },
    divide:     function(x,y){ return x/y; },
    pow:        Math.pow
};

function operate2(operation, operand1, operand2){
    if (typeof operators[operation] === "function")
        return operators[operation](operand1, operand2);
    else throw "unknown operator";
}

var j = operate2("add", "hello", operate2("add", " ", "world!"));
// j= "hello world!"
var k = operate2("pow", 10, 2);  // => k= 100
