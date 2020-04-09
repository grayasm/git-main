/* Cap.3 Types, Values and Variables
   3.1.1 Integer Literals

   JavaScript recognizes base-10, base-16, base-8 (non-standard).
*/

var decval = 3030;
var hexval = 0xff; // or 0XFF, 0xFF, 0Xff, 0XFf, 0xf all are 255 base-10.
var octval = 0377; // octal numbers start with a leading 0, this is 255 base-10.

/* ECMAScript standard does not support octal numbers.
   Some implementations allow them, in this format (leading 0).
   In strict mode of ECMAScript they are forbidden.
*/
