/* Cap.9 Classes and Modules
   9.2 Classes and Constructors

   $ node 02_class_constructor.js

   A constructor is a function designed for the initialization of newly created
   objects. Constructors are invoked using "new" keyword. Because they are
   special compared with regular functions we givem them names that start with
   capital letters.
*/

// This is a constructor function that initializes new Range objects.
// It does not create or return the object. It just initializes this.
function Range(from, to) {
    this.from = from;
    this.to = to;
}


// All Range objects inherit from this object.
// The property name must be "prototype" for this to work.
Range.prototype = {
    includes: function(x) { return this.from <= x && x <= this.to; },
    foreach: function(f) {
        for(var x = Math.ceil(this.from); x <= this.to; x++) f(x);
    },
    toString: function() { return "(" + this.from + "..." + this.to + ")"; }
};


// Uses of a Range object
var r = new Range(1,3);       // Create a Range object using "new" keyword
r.includes(2);                // true
r.foreach(console.log);       // 1 2 3
console.log(r);               // (1...3)
