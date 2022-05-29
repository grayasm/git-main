/* Cap.9 Classes and Modules
   9.5.3 The Constructor Name

   $ node 09_identity_constructor_name.js

   The main problem with using the instanceof operator or the constructor
   property for determining the class of an object occurs when there are
   multiple execution contexts and thus multiple copies of the constructor
   functions. These functions may well be identical, but they are distinct
   objects and are therefore not equal to each other.

   One possible workaround is to use the name of the constructor function as
   the class identifier rather than the function itself.
*/


/* Return the type of o as a string:
   - If o is null, return "null", if o is NaN, return "nan"
   - If typeof return a value other than "object" return that value.
     (Note that some implementations identify regexps as functions.)
   - If the class of o is anything other than "Object", return that.
   - If o has a constructor and that constructor has a name, return it.
   - Otherwise, just return "Object"
*/
function type(o) {
    var t, c, n;    // type, class, name

    // Special case for the null value:
    if (o === null) return "null";

    // Another special case: NaN is the only value not equal to itself:
    if (o !== o) return "nan";

    // Use typeof for any value other than "object".
    // This identifies any primitive value and also functions.
    if ((t = typeof o) !== "object") return t;

    // Return the class of the object unless it is "Object".
    // This will identify most native objects.
    if ((c = classof(o)) !== "Object") return c;

    // Return the object's constructor name, if it has one.
    if (o.constructor && typeof o.constructor === "function" &&
        (n = o.constructor.getName())) return n;

    // We can't determine a more specific type, so return "Object"
    return "Object";
}

// Return the class of an object.
function classof(o) {
    return Object.prototype.toString.call(o).slice(8,-1);
};

// Return the name of a function (may be "") or null for nonfunctions
Function.prototype.getName = function() {
    if ("name" in this) return this.name;
    return this.name = this.toString().match(/function\s*([^(]*)\(/)[1];
};



// Use of method type(o):

// This constructor has no name
var Complex = function(x,y) { this.r = x; this.i = y; }
var c = new Complex();

console.log( type(c) );                   // => Complex
console.log( type(Complex) );             // => function

// This constructor does have a name
var Range = function Range(f, t) { this.from = f; this.to = t; }
var r = new Range(1,3);

console.log( type(r) );                   // => Range
console.log( type(Range) );               // => function
