/* Cap.3 Types, Values and Variables
   3.2   Text
   3.2.1 String Literals

   JavaScript uses UTF-16 encoding and strings are sequences of unsigned 16-bit
   values. The Unicode characters whose codepoints to not fit in 16 bits are
   encoded following the rules of UTF-16 as a sequence of two 16-bit values.
*/

var p = "π"; // 1 character with 16-bit codepoint 0x03c0
var e = "𝑒"; // 1 character with 17-bit codepoint 0x1d452
p.length     // => 1: 1 16-bit element
e.length     // => 2: 2 16-bit values: "\ud835\udc52"


// The string characters are enclosed within ' or " quotes.

var s0 = ""; // the empty string: it has zero characters
var s1 = 'testing';
var s2 = "3.14";
var s3 = 'name="myform"';
var s4 = "Wouldn't you prefer O'Reilly's book?";
var s5 = "This string\nhas two lines";
var s6 = "π is the ratio of a circle's circumference to its diameter";

// ECMAScrip 5 allows to break a string literal across multiple lines with \
var s7 = "one\
 long\
 line";  // "one long line"


/* When combining JavaScript and HTML it is a good idea to use one style of
   quotes for JavaScript and the other style for HTML.
*/
<button onclick="alert('Thank you')">Click Me</button>
