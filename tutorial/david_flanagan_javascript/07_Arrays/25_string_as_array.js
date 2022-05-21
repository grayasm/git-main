/* Cap.7 Arrays
   7.12 Strings as Arrays

   $ node 25_string_as_array.js

   In ECMAScript 5 strings behave like read-only arrays.
*/

var s = "test";
s.charAt(0); // => "t"
s[1];        // => "e"


var s = "JavaScript";
Array.prototype.join.call(s, " ");  // => J a v a S c r i p t
Array.prototype.filter.call(
    s,                              // Filter the characters of the s
    function(x) {
        return x.match(/[^aeiou]/); // Only match nonvowels
    }).join("");                    // => "JvScrpt"
