/* Cap.6 Objects
   6.4 Testing Properties

   $ node 10_property_test.js

   Test a property with 'in' operator, methods hasOwnProperty() and
   propertyIsEnumerable(), or '!==' operator to make sure is not undefined.
*/

// The 'in' operator expects a property name (as a string) on its left side and
// an object on its right. It returns true if the object has an own property
// or an inherited property by that name.

var o = { x: 1 };
var t1 = "x" in o;        // true
var t2 = "y" in o;        // false
var t3 = "toString" in o; // true, o inherits a toString property

console.log(t1);          // true
console.log(t2);          // false
console.log(t3);          // true
console.log("---");

// The hasOwnProperty() method of an object tests whether that object has an
// own property with the given name. It returns flase for the inherited properties.

var t1 = o.hasOwnProperty("x");
var t2 = o.hasOwnProperty("y");
var t3 = o.hasOwnProperty("toString");

console.log(t1);   // true
console.log(t2);   // false
console.log(t3);   // false
console.log("---");


// The propertyIsEnumerable() refines the hasOwnProperty() test. If returns true
// only if the named property is an own property and its enumerable attribute
// is true. Certain built-in properties are not enumerable.

function inherit(p) {

    if (p == null)
        throw TypeError();    // p must be a non-null object
    if (Object.create)
        return Object.create(p);

    var t = typeof p;
    if (t != "object" && t != "function")
        throw TypeError();

    function f() {}           // Define a dummy constructor function.
    f.prototype = p;
    return new f();
}


var o = inherit( { y:2 } );
o.x = 1;
var t1 = o.propertyIsEnumerable("x");
var t2 = o.propertyIsEnumerable("y");
var t3 = Object.prototype.propertyIsEnumerable("toString");

console.log(t1);    // true
console.log(t2);    // false
console.log(t3);    // false
console.log("---");


// Instead of using the 'in' operator it is often sufficient to simply query
// the property and use !== to make sure it is not undefined.

var o = { x:1 };
var t1 = o.x !== undefined;
var t2 = o.y !== undefined;
var t3 = o.toString !== undefined;

console.log(t1);   // true
console.log(t2);   // false
console.log(t3);   // true
console.log("---");


// There is one thing the 'in' operator can do that the simple property access
// technique shwon above cannot do. 'in' can distinguish between properties
// that do not exist and properties that exist but have been set to undefined.

var o = { x: undefined };

var t1 = o.x !== undefined;
var t2 = o.y !== undefined;
var t3 = "x" in o;
var t4 = "y" in o;

delete o.x;
var t5 = "x" in o;

console.log(t1);    // false
console.log(t2);    // false
console.log(t3);    // true
console.log(t4);    // false
console.log(t5);    // false
console.log("---");


// Note that the code above uses the '!==' operator instead of '!='
// '!==' and '===' distinguish between undefined and null.
