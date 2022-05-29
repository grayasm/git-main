/* Cap.9 Classes and Modules
   9.5.2 The constructor property

   $ node 08_identity_constructor_type.js

   Another way to identify the class of an object is to simply use the
   constructor property.
*/

function typeAndValue(x) {
    if (x == null) return "";    // Null and undefined don't have constructors

    switch(x.constructor) {
    case Number:  return "Number: " + x;
    case String:  return "String: '" + x + "'";
    case Date:    return "Date: " + x;
    case RegExp:  return "Regexp: " + x;
    case Complex: return "Complex: " + x;
    }
}

console.log(typeAndValue(22));    // Number: 22
