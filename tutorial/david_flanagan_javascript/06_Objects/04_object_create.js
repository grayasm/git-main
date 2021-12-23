/* Cap.6 Objects
   6.1.4 Object.create()

   $ node 04_object_create.js


   ECMAScript 5 defines a method Object.create() that creates a new object.
*/


// Object.create() is a static function, not a method invoked on individual objects.
var o1 = Object.create({x:1, y:2});     // o1 inherits properties x and y
console.log(o1);                        // {}
console.log(o1.toString());             // [object Object]


// You can pass null to create a new object that does not have a prototype.
var o2 = Object.create(null);           // o2 inherits no props or methods


// If you want to create an ordinary empty object, pass Object.prototype
var o3 = Object.create(Object.prototype); // o3 is like {} or new Object().


// Example 6-1 Creating a new object that inherits from a prototype.
// inherit() returns a newly created object that inherits properties from the
// prototype object p. It uses the ECMAScript 5 function Object.create() if
// is is defined, and otherwise falls back to an older technique.
function inherit(p) {

    if (p == null) throw TypeError();     // p must be a non-null object
    if (Object.create)
        return Object.create(p);

    var t = typeof p;
    if (t != "object" && t != "function") throw TypeError();

    function f() {}                       // Define a dummy constructor function.
    f.prototype = p;
    return new f();
}
