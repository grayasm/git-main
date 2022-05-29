/* Cap.9 Classes and Modules
   9.3 Java-Style Classes in JavaScript

   $ node 05_class_java_style.js

   In Java or a similar strongly-typed object-oriented language, you may be
   acoustomed to thinking about four kind of class members:

   Instance fields: per-instance properties or variables.
   Instance methods: shared by all instances of the class.
   Class fields: properties or variables associated with the class (static?).
   Class methods: methods associated with the class (static?).

   In JavaScript, we can reduce the process of class definition to a three-step
   algorithm. First, write a constructor function that sets instance properties
   on new objects. Second, define instance methods on the prototype object of
   the constructor. Third, define class fields and class properties on the
   constructor itself.
*/

// (1). Write a constructor function.
function Complex(real,imaginary) {
    if (isNaN(real) || isNaN(imaginary))
        throw new TypeError();
    this.r = real;
    this.i = imaginary;
};


// (2). Define instance methods on the prototype object.
Complex.prototype.add = function(that) {
    return new Complex(this.r + that.r, this.i + that.i);
};

Complex.prototype.mul = function(that) {
    return new Complex(this.r * that.r - this.i * that.i,
                       this.r * that.i + this.i * that.r);
};

// The real magnitude of a complex number is its distance from the origin(0,0)
Complex.prototype.mag = function() {
    return Math.sqrt(this.r * this.r + this.i * this.i);
};

Complex.prototype.neg = function() { return new Complex(-this.r, -this.i); };

Complex.prototype.toString = function() {
    return "{" + this.r + "," + this.i + "}";
};

Complex.prototype.equals = function(that) {
    return that != null &&                      // Must be defined and non-null
        that.constructor === Complex &&         // and an instance of Complex
        this.r === that.r && this.i === that.i; // and have the same values.
};

// (3). Define class fields and class properties on the constructor itself.
Complex.ZERO = new Complex(0,0);
Complex.ONE = new Complex(1,0);
Complex.I = new Complex(0,1);

Complex.parse = function(s) {
    try {
        var m = Complex._format.exec(s);        // Regular expression magic
        return new Complex(parseFloat(m[1]), parseFloat(m[2]));
    }
    catch(x) {
        throw new TypeError("Can't parse '" + s + "' as a complex number.");
    }
};

// A "private" class field used in Complex.parse() above.
// The underscore in its name indicates that is is intended for internal use and
// should not be considered part of the public API of this class.
Complex._format = /^\{([^,]+),([^}]+)\}$/;


// Example of how to use class Complex:
var c = new Complex(2,3);
var d = new Complex(c.i, c.r);
c.add(d).toString();                                           // => {5,5}
Complex.parse(c.toString()).add(c.neg()).equals(Complex.ZERO); // => true
