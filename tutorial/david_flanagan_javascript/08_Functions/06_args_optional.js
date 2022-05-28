/* Cap.8 Functions
   8.3.1 Optional Parameters

   $ node 06_args_optional.js

   JavaScript does not check the type or number of arguments being passed.
   When a function is invoked with fewer arguments than declared parameters,
   the additional parameters are set to undefined.
*/

function getPropertyNames(o, /*optional*/ a){
    if (a === undefined) a = [];
    for (var property in o)
        a.push(property);
    return a;
}

var o = { x:1 };
var p = { y:1 };

var a = getPropertyNames(o);      // => x
var b = getPropertyNames(p, a);   // => x,y
