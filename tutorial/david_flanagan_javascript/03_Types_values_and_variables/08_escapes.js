/* Cap.3 Types, Values and Variables
   3.2.2 Escape Sequences in String Literals

   Escape sequences are formed as usual using backslash character \
*/

var s0 = 'You\'re right, it can\'t be a quote';
var s1 = '\xA9';    // "©" represented as \x Hexadecimal number
var s2 = '\u03c0';  // "π" represented as \u Unicode character

/*
  \0          The NULL character (\u0000)
  \b          Backspace (\u0008)
  \t          Horizontal tab (\u0009)
  \n          Newline (\u000A)
  \v          Vertical tab (\u000B)
  \f          Form feed (\u000C)
  \r          Carriage return (\u000D)
  \"          Double quote (\u0022)
  \'          Apostrophe or single quote (\u0027)
  \\          Backslash (\u005C)
  \xXX        The Latin-1 character specified by the two hex digits XX
  \uXXXX      The Unicode character specified by the four hex digits XXXX
*/
