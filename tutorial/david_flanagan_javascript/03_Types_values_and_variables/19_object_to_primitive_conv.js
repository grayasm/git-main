/* Cap.3 Types, Values and Variables
   3.8.3 Object to Primitive Conversions

   $ node 19_object_to_primitive_conv.js

   Object to boolean:
       - all objects including arrays and functions convert to true.
       - new Boolean(false) converts to true.

   Object to string:
       - all Objects inherit 2 methods: toString(), valueOf()
       - if the object implements toString() then conversion calls it, otherwise
       - if the object implements valueOf() then calls it and if the returned
         value is a primitive is converted to string, otherwise
       - throws a TypeError

   Object to number:
       - if the object implements valueOf() then conversion calls it, otherwise
       - if the object implements toString() then calls it and converts the
         returned string to number, otherwise
       - throws TypeError
*/


// Object to boolean
var a = new Boolean(false);
if (a) console.log("if(a) is TRUE");    // if(a) is TRUE
else   console.log("if(a) is FALSE");


// Object to string  (using a generic object)
var a = {x:1, y:2};
console.log(  a.toString()  );         // [object Object]

// Object to string  (using custom toString())
function classA(x, y) {
    this.x = x;
    this.y = y;
};

classA.prototype.toString = function() {
    return "(" + this.x + ", " + this.y + ")";
}

var a = new classA(-1, -2);
console.log(  a.toString()  );        // (-1, -2)

// Object to number  (using custom valueOf())
function classB(x, y) {
    this.x = x;
    this.y = y;
}

classB.prototype.valueOf = function() {
    return this.x + this.y;
}

var b = new classB(1000, -1);
console.log(1 + b);                   // 1000

// Array to string
console.log(  [1,2,3].toString() );   // 1,2,3

// Function to string
var floor = function(x) { return Math.floor(x); }
console.log(  floor.toString()   );   // function(x) { return Math.floor(x); }

// RegExp to string
console.log(  /\d+/g.toString()  );   // /\d+/g

// Date to string
var d = new Date(2010,0,1);
console.log(  d.toString()       );   // Fri Jan 01 2010 00:00:00 GMT+0100 (Central European Standard Time)

// Date to number
console.log(  d.valueOf()        );   // 1262300400000

// Date conversions
var d = new Date();
console.log(  typeof(d + 1)      );   // string
console.log(  typeof(d - 1)      );   // number
