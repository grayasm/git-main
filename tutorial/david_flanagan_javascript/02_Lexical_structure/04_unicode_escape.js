/* Cap.2 Lexical Structure
   2.1.3 Unicode Escape Sequences

   Some computer hardware and software cannot display or input the full set of
   Unicode characters. To support programmers using this older technology,
   JavaScript defines special sequences of six ASCII characters to represent
   any 16-bit Unicode codepoint. The Unicode escape begins with \u followed
   by 4 hexadecimal digits.

   Unicode escapes may appear in JavaScript:
       string literals
       regular expression
       literals and in identifiers (but not in language keywords)
       comments
*/

var test = "café" === "caf\u00e9"
console.log("test is: " + test)      // test is: true
