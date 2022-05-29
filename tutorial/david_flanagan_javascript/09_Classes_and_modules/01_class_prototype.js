/* Cap.9 Classes and Modules
   9.1 Classes and Prototypes

   $ node 01_class_prototype.js

   A class is a set of objects that inherit properties from the same prototype.
*/


/* A class representing a range of values.

   The class is initialized by a factory method (e.g. "range")
   The class is not initialized by a constructor because:
    a) a constructor always defines the "prototype" object (see .methods object)
    b) a constructor does not create nor return an object (see return r;)
*/
function range(from, to) {
    var r = inherit(range.methods);
    r.from = from;
    r.to = to;
    return r;
}

// This prototype object defines methods inherited by all range objects.
range.methods = {
    // Return true if x is in the range, false otherwise.
    includes: function(x) { return this.from <= x && x <= this.to; },

    //Invoke f once for each integer in the range.
    foreach: function(f) {
        for(var x = Math.ceil(this.from); x <= this.to; x++) f(x);
    },

    // Return a string representation of the range.
    toString: function() { return "(" + this.from + "..." + this.to + ")"; }
};

// see inherit(..) in 06_Objects/07_property_as_inheritance.js
function inherit(p) {

    if (p == null)
        throw TypeError();          // p must be a non-null object

    if (Object.create)
        return Object.create(p);

    var t = typeof p;
    if (t != "object" && t != "function")
        throw TypeError();

    function f() {}                 // Define a dummy constructor function.
    f.prototype = p;
    return new f();
}


// Here are examples of uses of a range object.
var r = range(1,3);                   // Create a range object
r.includes(2);                        // true
r.foreach(console.log);               // 1 2 3
console.log(r);                       // (1...3)
