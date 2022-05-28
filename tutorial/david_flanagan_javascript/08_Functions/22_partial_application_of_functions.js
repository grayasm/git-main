/* Cap.8 Functions
   8.8.3 Partial Application of Functions

   $ node 22_partial_application_of_functions.js

   The bind() method partially applies arguments on the left—that is,
   the arguments you pass to bind() are placed at the start of the argument list
   that is passed to the original function. But it is also possible to partially
   apply arguments on the right.
*/


function array(a, n){ return Array.prototype.slice.call(a, n || 0); }

function partialLeft(f /*, ...*/){
    var args = arguments;
    return function() {
        var a = array(args, 1);
        a = a.concat(array(arguments));
        return f.apply(this, a);
    };
}

function partialRight(f /*, ...*/){
    var args = arguments;
    return function(){
        var a = array(arguments);
        a = a.concat(array(args, 1));
        return f.apply(this, a);
    };
}

function partial(f /*, ...*/){
    var args = arguments;
    return function(){
        var a = array(args, 1);
        var i=0, j=0;
        for(; i < a.length; i++)
            if (a[i] === undefined) a[i] = arguments[j++];
        a = a.concat(array(arguments, j));
        return f.apply(this, a);
    };
}

var f = function(x,y,z) { return x*(y-z); };
partialLeft(f, 2)(3,4);         // => -2: Bind first argument: 2 * (3 - 4)
partialRight(f, 2)(3,4);        // =>  6: Bind last argument: 3 * (4 - 2)
partial(f, undefined, 2)(3,4);  // => -6: Bind middle argument: 3 * (2 -4)
