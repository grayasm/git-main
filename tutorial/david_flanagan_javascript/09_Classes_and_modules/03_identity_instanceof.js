/* Cap.9 Classes and Modules
   9.2.1 Constructor and Class Identity

   $ node 03_identity_instanceof.js

   r instanceof Range => returns true if r inherits from Range.prototype.

   The name of the constructor is not essential to establish the identity
   of a class, but its "prototype" object.
*/


function Range(from, to) {
    this.from = from;
    this.to = to;
}
// The identity of Range class is this "prototype" object.
Range.prototype = {
    includes: function(x) { return this.from <= x && x <= this.to; },
    foreach: function(f) {
        for(var x = Math.ceil(this.from); x <= this.to; x++) f(x);
    },
    toString: function() { return "(" + this.from + "..." + this.to + ")"; }
};

function RangeEx(from, to) {
    this.from = from;
    this.to = to;
}
// The identity of RangeEx class is Range's prototype.
RangeEx.prototype = Range.prototype;

var r1 = new Range(1,3);
var r2 = new RangeEx(1,4);


r1 instanceof Range;        // true
r2 instanceof Range;        // true <- although it has a different constructor!
