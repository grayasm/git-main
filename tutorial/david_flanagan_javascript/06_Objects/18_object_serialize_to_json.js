/* Cap.6 Objects
   6.9   Serializing Objects

   $ node 18_object_serialize_to_json.js


   Object serialization is the process of converting an object’s state to
   a string from which it can later be restored.

   Reference:
   JSON.stringify()
   JSON.parse()
*/


o = { x:1, y: { z: [false, null, ""] } };  // a test object
s = JSON.stringify(o);

console.log(s);             // {"x":1,"y":{"z":[false,null,""]}}

p = JSON.parse(s);          // p is a deep copy of o

console.log(o == p);        // false
