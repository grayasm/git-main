/* Cap.6 Objects
   6.7.1 Legacy API for Getters and Setters

   $ node 14_property_legacy_api.js


   This API consists of four methods available on all objects.
   __lookupGetter__() and __lookupSetter__() return the getter or setter
   method for a named property. And __defineGetter__() and __defineSetter__()
   define a getter or setter: pass the property name first and the getter or
   setter method second.
*/

var a = {
    x: 0,
    get value() { return this.x; },
    set value(x) { this.x = x; }
};

console.log(a.__lookupGetter__("value"));    // [Function: get value]
console.log(a.__lookupSetter__("value"));    // [Function: set value]
