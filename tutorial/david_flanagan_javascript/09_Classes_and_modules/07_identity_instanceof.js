/* Cap.9 Classes and Modules
   9.5.1 The instanceof operator

   $ node 07_identity_instanceof.js

   In JavaScript "A instanceof B" checks if A inherits from B.
   The inheritance need not be direct (e.g. A inherits P inherits Q inherits B)
   In JavaScript constructors act as the public identity of the classes, but
   prototypes are the fundamental identity.
*/

function A(x) {
    this.x = x;
};

function B(y) {
    this.y = y;
};
B.prototype = A.prototype;

function C(z) {
    this.z = z;
};
C.prototype = B.prototype;

var a = new A(0);
var b = new B(1);
var c = new C(2);

console.log(c instanceof A);    // => true

A.prototype.isPrototypeOf(c);   // => true
