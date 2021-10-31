/* Cap.6 Objects
   The Object:
       > is the JavaScript's fundamental datatype,
       > is an unordered collection of properties, each with a name and a value
       > property name is a string which maps to a value
       > property name may be any string, including the empty string
       > string-to-value mapping is also known as: hash, hashtable, dictionary
       > cannot have two properties with the same name
       > property value may be any value or may be a getter or a setter function
         or both.

       > inherits the properties of another object, known as its "prototype"
       > is dynamic, as properties can be added and deleted
       > is everything else that is not a string, a number, true, false, null or undefined
       > is mutable and manipulated by reference, not by value,
         var y = x; holds a reference and modifications to y are visibile to x;

       > property attributes are writable, enumerable, configurable:
         >> writable    : whether the value of the property can be set
         >> enumerable  : whether the property name is returned by a for/in loop
         >> configurable: whether the property can be deleted and its attributes can be altered

   The Object:
       > has 3 associated object attributes:
         >> prototype       : is a reference to another object from which properties are inherited
         >> class           : is a string that categorizes the type of an object
         >> extensible flags: whether new properties may be added to the object

   The Object classification:
       > native            : defined by ECMAScript (e.g. arrays, dates, regexp, etc)
       > host              : defined by the host environment-browser (e.g. HTMLElement object)
       > user-defined      : any object created by the execution of JavaScript code
       > own-property      : a property defined directoy on an object
       > inherited-property: a property defined by an object's prototype object

   6.1.1 Object Literals

   $ node 01_object_literals.js

*/

var empty = {};                                 // An object with no properties
var point = { x:0, y:0};                        // Two properties
var point2 = { x:point.x, y:point.y+1 };        // More complex values

var book = {
    "main title": "JavaScript",                 // Property names include spaces
    'sub-title': "The Definitive Guide",        // and hyphens, so use string literals
    "for": "all audiences",                     // for is a reserved word, so quote
    author: {                                   // The value of this property is
        firstname: "David",                     // itself and object. Note that
        surname: "Flanagan"                     // these property names are unquoted.
    }
};
