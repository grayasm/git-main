/* Cap.9 Classes and Modules
   9.2.2 The constructor Property

   $ node 04_identity_constructor.js

   Any JavaScript function can be used as a constructor, and constructor
   invocations need a prototype property. Therefore, every JavaScript function
   automatically has a prototype property. The value of this property is an
   object that has a single nonenumerable constructor property.
*/


var F = function(){};         // Function object definition.
var p = F.prototype;          // The prototype object of function F.
var c = p.constructor;        // The "constructor" definition of function F.
console.log(c === F);         // => true

var o = new F();
var t = o.constructor;        // The "constructor" member of object o.
console.log(t === F);         // => true



// In the previous Range example there was no constructor defined in the
// prototype object. We can remedy the issue now.

function Range(from,to) {
    this.from=from;
    this.to=to;
};

Range.prototype = {
    constructor: Range,       // Explicitly set the constructor back-reference.
    includes: function(x) { return this.from <= x && x <= this.to; },
    foreach: function(f) {
        for(var x = Math.ceil(this.from); x <= this.to; x++)
            f(x);
    },
    toString: function() { return "(" + this.from + "..." + this.to + ")";}
};

var r = new Range(1,3);
var p = r.prototype;
var c = r.constructor;
console.log(c === Range);     // => true
