/* Cap.7 Arrays
   7.8.1 join()

   $ node 08_method_join.js

   Array.join() concatenates all elements into one string.
*/

var a = [1, 2, 3];
a.join();            // => "1,2,3"
a.join(" ");         // => "1 2 3"
a.join("");          // => "123"

var b = new Array(10);// An array of length 10 with no elements
b.join('-');          // => '----------': a string of 9 hyphens
