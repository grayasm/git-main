/* Cap.4 Expressions and Operators
   4.10.2 Logical OR ||

   $ node 18_logical_OR.js
*/

// Idiom for function body with default values for parameters
function copy(o, p) {
    p = p || {};      // if no object passed for p, use a newly created object/
    // function body goes here
    // ...
}
