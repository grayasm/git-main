/* Cap.6 Objects
   6.1.2 Creating Objects with new

   > 'new' operator creates and initializes a new object
   > 'new' keyword is followed by a function called constructor
   > JavaScript includes buit-in constructors for native types


   $ node 02_object_new.js
*/


var o = new Object();       // create an empty object: same as {}
var a = new Array();        // create an empty array: same as []
var d = new Date();         // create a Date object repr the current time
var r = new RegExp("js");   // create a RegExp object for pattern matching
