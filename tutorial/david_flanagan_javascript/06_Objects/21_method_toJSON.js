/* Cap.6 Objects
   6.10.3 The toJSON() Method

   $ node 21_method_toJSON.js

   Object.prototype does not actually define a toJSON() method, but the
   JSON.stringify() method looks for a toJSON() method on any object it is
   asked to serialize. If this method exists on the object to be serialized,
   it is invoked, and the return value is serialized, instead of the original
   object.
*/
