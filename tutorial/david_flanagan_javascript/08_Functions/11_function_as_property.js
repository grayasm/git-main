/* Cap.8 Functions
   8.4.1 Defining Your Own Function Properties

   $ node 11_function_as_property.js

   Functions are not primitive values in JavaScript, but a specialized kind of
   object, which means that functions can have properties.
   When a function needs a “static” variable whose value persists across
   invocations, it is often convenient to use a property of the function,
   instead of cluttering up the namespace by defining a global variable.
*/

// Initialize the counter property of the function object.
uniqueInteger.counter = 0;

function uniqueInteger() {
    return uniqueInteger.counter++;
}

console.log("uniqueInteger = " + uniqueInteger());    // => 0
console.log("uniqueInteger = " + uniqueInteger());    // => 1
console.log("uniqueInteger = " + uniqueInteger());    // => 2
