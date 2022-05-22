/* Cap.8
   8.6 Closures

   $ node 13_closures.js

   The combination of a function object and a scope in which the function's
   variables are resolved is called a closure in the CS literature.

   The syntax would be something like this:

   var f = (function(){
       ... private vars ...
       return function(){ ... }
       }());
*/

var scope = "global scope";
function checkscope() {
    var scope = "local scope";
    function f() { return scope; }
    return f();
}
checkscope();        // => "local scope"

function checkscope2() {
    var scope = "local scope";
    function f() { return scope; }
    return f;
}
checkscope2()();    // => "local scope" ????

/*
   In C the local variables defined in the outer function cease to exist when
   the outer function returns, so how can the nested function execute using
   a scope chain that does not exist anymore?

   Each time a JavaScript function is invoked, a new object is created to hold
   the local variables for that invocation, and that object is added to the
   scope chain.

   Closures capture the local variables of a single function invocation and
   can use those variables as private state. Here is how we could rewrite the
   uniqueInteger() function using closures:
*/

var uniqueInteger = (function() {
    var counter = 0;
    return function() { return counter++; };
}());

console.log(uniqueInteger()); // => 0
console.log(uniqueInteger()); // => 1
console.log(uniqueInteger()); // => 2



/*
  It is perfectly possible for two or more nested functions to be defined
  within the same outer function and share the same scope chain.
*/
function counter(){
    var n = 0;
    return {
        count: function() { return n++; },
        reset: function() { n = 0; }
    };
}

var c = counter(), d = counter();     // Create 2 counters
c.count();                            // => 0
d.count();                            // => 0: they count independently
c.reset();                            // count() and reset() share the state
c.count();                            // => 0: because we reset c
d.count();                            // => 1: d was not reset
