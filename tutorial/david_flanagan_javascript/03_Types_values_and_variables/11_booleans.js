/* Cap.3 Types, Values and Variables
   3.3.  Boolean Values

   Boolean values can be true or false.

   Any JavaScript value can be converted to a boolean value.
   The following 6 values convert to, and work like false:
       undefined
       null
       0
       -0
       NaN
       ""   // the empty string

   All other values, including all objects and arrays convert to true.
   These avalues are called sometimes "truthy" and "falsy".
   Boolean values have a toString() that converts to strings "true" or "false".
   There are 3 important boolean operators: && || and !  (AND, OR and NOT).
*/


function Obj(x) {
    this.x = x;
}
var o = new Obj(5);
console.log("o object has x=" + o.x);

if (o != null) console.log("o is not null"); // Both expressions are similar and
if (o)         console.log("o is not null"); // we can rely on the fact that
                                             // null is falsy
                                             // and objects are truthy.

// The 3 boolean operators && || and !
var x=1, y=2, z=3;
if ((x == 0 && y == 0) || !(z == 0)){
    console.log("x and y are both zero or z is non-zero");
}
