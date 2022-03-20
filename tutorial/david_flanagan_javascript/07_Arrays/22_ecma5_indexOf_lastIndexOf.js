/* Cap.7 Arrays
   7.9.6 indexOf() and lastIndexOf()

   $ node 22_ecma5_indexOf_lastIndexOf.js

   Both method search an aray for an element with a specified value and
   return the index of such element or -1 if none is found.
*/


a = [0,1,2,1,0]
a.indexOf(1);    // => 1
a.lastIndexOf(1);// => 3
a.indexOf(3);    // => -1, no element has value 3


// The following function searches an array for a specified value and returns
// and array of all matching indexes. The second argument of indexOf() can be
// used to find matches beyond the first.

var a = [3,2,1,2,3,3]

function findall(a, x) {
    var results = [],
        len = a.length,
        pos = 0;
    while (pos < len) {
        pos = a.indexOf(x, pos);
        if (pos === -1) break;
        results.push(pos);
        pos = pos + 1;
    }
    return results;
}

console.log(findall(a, 3)); // => [0, 4, 5]
