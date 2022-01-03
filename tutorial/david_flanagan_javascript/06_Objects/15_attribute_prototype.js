/* Cap.6 Objects
   6.8.1 The prototype Attribute

   $ node 15_attribute_prototype.js


   Every object has associated prototype, class, and extensible attributes.
   Reference:
   Object.getPrototypeOf()
   Object.create()
   Object.isPrototypeOf()
*/


var p = { x:1 };                      // define a prototype object
var o = Object.create(p);             // create an object with that prototype
p.isPrototypeOf(o);                   // => true: o inherits from p
Object.prototype.isPrototypeOf(o);    // => true: o inherits from Object.prototype
