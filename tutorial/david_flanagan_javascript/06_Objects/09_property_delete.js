/* Cap.6 Objects
   6.3 Deleting Properties

   $ node 09_property_delete.js
*/

// The delete operator removes a property from an object.
book = {
    "main title": "JavaScript: The Definitive Guide",
    author: {
        name: "David",
        surname: "Flanagan"
    },
    edition:3
};

delete book.author;
delete book["main title"];

console.log(book);    // { edition: 3 }

// The delete operator only deletes own properties, not inherited ones.
// To delete an inherited property, you must delete it from the prototype object
// in which it is defined. Doing this affects every object that inherits from
// that prototype.

o = { x:1 };        // o has own property x and inherits property toString
delete o.x;         // delete x, and return true
delete o.x;         // do nothing (x doesn't exist), and return true
delete o.toString;  // do nothing (toString isn't an own property), return true
delete 1;           // nonsense, but evalutates to true


// delete does not remove properties that have a configurable attribute of false.
// Certain properties of built-in objects are nonconfigurable, as are the
// properties of the global object created by variable declaration and function
// declaration. In non-strict mode (and in ECMAScript 3) delete simply evaluates
// to false

delete Object.prototype;  // Can't delete; property is non-configurable
var x = 1;                // Declare a global variable
delete this.x;            // Can't delete this property
function f() {}           // Declare a global function
delete this.f;            // Can't delete this property either


// When deleting configurable properties of the global object in non-strict mode
// you can omit the reference to the global object (this).

this.x = 1;               // Create a configurable global property (no var)
delete x;                 // And delete it

// In strict mode, however, delete raises a SyntaxError if its operand is an
// unqualified identifier like x, and you have to be explicit about the
// property access:

delete x;                 // SyntaxError in strict mode
delete this.x;            // This works
