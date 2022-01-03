/* Cap.6 Objects
   6.6 Properties Getters and Setters

   $ node 12_property_getters_and_setters.js

   Getters and setters allow you to define Object Accessors,
*/

var o = {
    x : 0,
    get value()  { return this.x; },
    set value(v) { this.x = v; }
}

console.log("o.value=" + o.value);    // calls getter function
o.value = 20;                         // calls setter function
console.log("o.value=" + o.value);    // calls getter function


/* Accessor properties are inherited, just as data properties are. */

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

var p = inherit(o);
console.log("p.value=" + p.value);  // 20
p.value = 30;                       // p.x is 30, o.x remains unchanged
console.log("p.value=" + p.value);  // 30
console.log("o.value=" + o.value);  // 20


/*
 * Other reasons to use accessor properties include sanity checking of
 * property writes and returning different values on each property.
 */
var serial = {
    n : 0,

    get next() { return this.n++; },

    set next(n) {
        if (n > this.n)  this.n = n;
        else  throw "serial number can only be set to a larger value";
    }
}

try {
    console.log("serial.next = " + serial.next);  // 0
    console.log("serial.next = " + serial.next);  // 1
    serial.next = 0;                              // exception
} catch(e) {
    console.log("caught e=" + e);
}


/* Finally, here is one more example that uses a getter method to implement
 * a property with “magical” behavior.
 */
var random = {
    get octet() { return Math.floor(Math.random()*256); },
    get uint16() { return Math.floor(Math.random()*65536); },
    get int16() { return Math.floor(Math.random()*65536)-32768; }
};

console.log("random.octet = " + random.octet);    // 253
console.log("random.uint16= " + random.uint16);   // 22902
console.log("random.int16 = " + random.int16);    // -7892
