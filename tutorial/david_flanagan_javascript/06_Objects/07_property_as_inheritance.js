/* Cap.6 Objects
   6.2.2 Inheritance

   $ node 07_property_as_inheritance.js

   Objects have a set of "own properties" and they also inherit a set of
   properties from their prototype object.
*/

// Suppose you query the property x in the object o. If o does not have an
// own property with that name, the prototype of o is queried for x.
// If the prototype does not have an own property x but has a prototype itself
// the query is performed on the prototype of the prototype. This continues
// until the property x is found or until and object with a null prototype is
// searched.

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

var o = {}
o.x = 1;
var p = inherit(o);
p.y = 2;
var q = inherit(p);
q.z = 3;
var s = q.toString();
var r = q.x + q.y;

console.log(r);                     // 3: x and y are inherited from o and p


// another example
var unit_circle = { r:1 };          // an object to inherit from
var c = inherit(unit_circle);       // c inherits the property r
c.x = 1; c.y = 1;                   // c defines two properties of its own
c.r = 2;                            // c overrides its inherited property
console.log(unit_circle.r);         // 1: the prototype object is not affected
