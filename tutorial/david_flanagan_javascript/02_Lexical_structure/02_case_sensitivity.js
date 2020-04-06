/* Cap.2 Lexical Structure
   2.1.1 Case Sensitivity

   JavaScript is a case-sensitive language. Language keywords, variables,
   function names and other identifiers must always be typed with a consistent
   capitalization of letters.
*/

//The while keyword, for example, must be typed "while", not "While" or "WHILE"

var i = 0;
// WHILE(i < 3) { error: Unexpected token {
while(i < 3) {
    console.log("i = " + i++);
}

/*output:
i = 0    VM342:5
i = 1    VM342:5
i = 2    VM342:5
*/
