/* Cap.3 Types, Values and Variables
   3.6 Wrapper Objects

   $ node 14_wrapper_objects.js

   For example a "string" is not an object so why does it have methods like
   substring(...) and indexOf(...) and so on? Because the JS implementation
   creates a wrapper objects around the basic types - String, Number, Boolean.

   Here is how it works:

   1. JS converts the string value to String object via new String(s).
   2. JS resolves the properties of the object: substring(..), indexOf(..), etc.
   3. JS discards the transient object.


   - string, number and boolean values differ from objects:
     * their properties are read-only,
     * you can't define new properties on them.
   - you can explictly create wrapper objects by invoking
     * new String(..)
     * new Number(..)
     * new Boolean(..)
   - you get TypeError if attempt to wrapp: null or undefined.
   - operator ==  returns true  for s ==  new String(s)
   - operator === returns false for s === new String(s)
   - typeof(s)             is 'string'
   - typeof(new String(s)) is 'object'
*/

// "string" wrapped object
var s1 = "hello world!";
var word = s1.substring(s1.indexOf(" ")+1, s1.length);
console.log(word);    // world!

// Properties are read-only
var s2 = "test";      // start with a string value
s2.len = 4;           // set a property on the transient object <-- discarded
var t2 = s2.len;      // query the property <-- "len" property does not exist
console.log(t2);      // undefined ????

// Explicit wrappers
var s3 = "test", n3 = 1, b3 = true; // a string, number and boolean value.
var S3 = new String(s3);            // a String object
var N3 = new Number(n3);            // a Number object
var B3 = new Boolean(b3);           // a Boolean object

console.log(S3);                    // [String: 'test']
console.log(N3);                    // [Number: 1]
console.log(B3);                    // [Boolean: true]

console.log(typeof(s3))             // string
console.log(typeof(S3))             // object
