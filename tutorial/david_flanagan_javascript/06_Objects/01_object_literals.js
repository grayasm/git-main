/* Cap.6 Objects
   6.1.1 Object Literals

   $ node 01_object_literals.js

   var book = {

       "main title": "JavaScript",

       "for": "all audiences",

       author: {
           firstname: "David",
           surname: "Flanagan"
       }
   };

   JavaScript's fundamental datatype is the object.
   An object is an unordered collection of properties, each of which has
       a name and a value. Property names are strings, so we can say that
       objects map strings to values.
   JavaScript object inherits the properties of another object, know as "prototype"
   Objects are manipulated by reference rather than by value.
   Objects properties have attributes: writable, enumerable, configurable.
       The writeable attribute specifies whether the value of the property can be set.
       The enumerable attribute specifies whether the property name is returned by a for/in loop.
       The configurable attribute specifies whether the property can be deleted and whether its attributes can be altered.
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
