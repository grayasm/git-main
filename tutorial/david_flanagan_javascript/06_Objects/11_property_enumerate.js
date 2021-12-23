/* Cap.6 Objects
   6.5 Enumerating Properties

   $ node 11_property_enumerate.js

   Instead of testing for the existance of individual properties, we sometimes
   want to iterate through or obtain a list of all properties of an object.
*/

var o = {x:1, y:2, z:3};            // Three enumerable own properties
o.propertyIsEnumerable("toString"); // => false: not enumerable
for (p in o)                        // Loop through the properties
    console.log(p);                 // Prints x,y and z, but not toString


//If you want to skip the inherited properties returned by for/in do so:
for (p in o) {
    if (!o.hasOwnProperty(p)) continue; // skip inherited properties
    console.log(p);                 // Prints x,y and z
}

for (p in o) {
    if (typeof o[p] === "function") continue; // skip method
    console.log(p);
}

// Example 6-2. Object utility functions that enumerate properties
/* Copy the enumerable properties of p to o, and return o.
 * If o and p have a property by the same name, o's property is overwritten.
 * This function does not handle getters and setters or copy attributes.
 */

function extend(o, p) {
}
