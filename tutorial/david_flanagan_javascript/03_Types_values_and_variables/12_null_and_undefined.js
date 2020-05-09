/* Cap.3 Types, Values and Variables
   3.4   null and undefined

   null:
     - is a language keyword that evaluates to a special value
     - typeof(null) is "object" and can be thought of "no object"

   undefined:
     - a deeper kind of absence of a value
     - variables that have not been initialized
     - an object property or array element that does not exist
     - returned by functions that have no return value
     - values of function parameters for which no argument is supplied
     - typeof(undefined) is "undefined"

   both:
     - can be used interchangeably as they both indicate an absence of value
     - both equal with == , and not equal with ===
     - both "falsy" values and behave like false when a boolean is required
     - consider undefined like a system-level absence of value
     - consider null like a program-level absence of value
*/


var v;
console.log(v);             // undefined
console.log(typeof(v));     // undefined

v = null;
console.log(v);             // null
console.log(typeof(v));     // object

null === undefined          // false
null == undefined           // true
null === null               // true

null = 'value';             // Uncaught SyntaxError
undefined = 'value';        // ok
console.log(undefined);     // undefined

var a = ['a', 'b', 'c'];
delete a[1];
for (var i = 0; i < a.length; i++)
    console.log(i + ".) " + a[i]);

/* 0.) a
   1.) undefined
   2.) c
*/
