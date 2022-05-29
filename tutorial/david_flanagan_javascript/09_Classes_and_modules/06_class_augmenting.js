/* Cap.9 Classes and Modules
   9.4 Augmenting Classes

   $ node 06_class_augmenting.js

   An object inherits properties from its prototype, even if the prototype
   changes after the object is created. We can augment JavaScript classes
   simply by adding new methods to their prototype objects.
*/

function Complex(real,imaginary) {
    if (isNaN(real) || isNaN(imaginary))
        throw new TypeError();
    this.r = real;
    this.i = imaginary;
};

Complex.prototype.toString = function() {
    return "{" + this.r + "," + this.i + "}";
};

// Create a Complex object
var c = new Complex(2,3);

// Add a new method after the object "c" was created.
Complex.prototype.conj = function() { return new Complex(this.r, -this.i); };

// c will inherit conj() method also!
c.conj().toString();      // => {2,-3}
