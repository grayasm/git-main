/* Cap.6 Objects
   6.8.3 The extensible Attribute

   $ node 17_attribute_extensible.js


   The extensible attribute of an object specifies whether new properties
   can be added to the object or not.
   In ECMAScript 3, all built-in and user-defined objects are implicitly
   extensible.
   In ECMA-Script 5, all built-in and user-defined objects are extensible
   unless they have been converted to be nonextensible.

   Reference:
   Object.seal() or Object.preventExtensions()
   Object.isSealed()
   Object.freeze()
   Object.isFrozen()
*/


// Create a sealed object with a frozen prototype and a nonenumerable property
var o = Object.seal(Object.create(Object.freeze({x:1}),
                                  {y: {value: 2, writable: true}}));
console.log(o);  // {}
