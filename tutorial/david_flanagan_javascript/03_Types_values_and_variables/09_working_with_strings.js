/* Cap.3 Types, Values and Variables
   3.2.3 Working with Strings

   JavaScript has built-in feature to concatenate strings with + operator.
   string .length property contains the number of 16-bit values in the string.
   JavaScript contains a number of methods that work with strings - they do not
   modify the strings on which they are invoked, but return a new strings.
*/

var s1 = "Hello, " + "world";  // => "Hello, world"

var author = "Author Name";
var s2 = "Welcome to my blog," + " " + author;

var s3 = "hello, world"        // Start with some text.
s3.charAt(0)                   // "h"   the first character
s3.charAt(s3.length-1)         // "d"   the last character
s3.substring(1,4)              // "ell" the 2nd, 3rd and 4th characters
s3.slice(1,4)                  // "ell" same thing
s3.indexOf("l")                // 2     position of the first letter l
s3.lastIndexOf("l")            // 10    position of the last letter l
s3.indexOf("l",3)              // 3     position of first "l" at or after 3
s3.split(", ")                 // ["hello", "world"] split into substrings
s3.replace("h","H")            // "Hello, world"     replaces all instances
s3.toUpperCase()               // "HELLO, WORLD"
