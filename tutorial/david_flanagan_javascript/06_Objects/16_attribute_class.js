/* Cap.6 Objects
   6.8.2 The class Attribute

   $ node 16_attribute_class.js

   An object’s class attribute is a string that provides information about
   the type of the object. The default toString() method returns a string
   of the form:
   [object class]
*/


function classof(o) {
    if (o === null) return "Null";
    if (o === undefined) return "Undefined";
    return Object.prototype.toString.call(o).slice(8,-1);
}


console.log(  classof(null)  );           // Null
console.log(  classof(1)     );           // Number
console.log(  classof("")    );           // String
console.log(  classof(false) );           // Boolean
console.log(  classof({})    );           // Object
console.log(  classof([])    );           // Array
console.log(  classof(/./)   );           // RegExp
console.log(  classof(new Date()) );      // Date
//console.log(  classof(window)  );  "Window" (a client-side host object)
function f() {};
console.log(  classof(new f()) );         // Object
