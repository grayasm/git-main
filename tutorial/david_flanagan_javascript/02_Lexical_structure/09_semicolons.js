/* Cap.2 Lexical Structure
   2.5   Optional Semicolons

   JavaScript uses semicolon (;) to separate statements from each other.
   You can omit the semicolon between two statements if those statements are
   written on separate lines. JavaScript treats a line break as a semicolon
   if the next nonspace character cannot be interpreted as a continuation
   of the current statement.
*/

// Consider the following code:
var a
a
=
3
console.log(a)
// It is equal with:
// var a; a = 3; console.log(a);

/* These statement termination rules lead to some surprising cases. This code
   looks like two separate statements separated with a newline:
*/
var y = x + f
(a+b).toString()

/* But the parantheses on the second line of code can be interpreted as a
   function invocation of f from the first line, and JavaScript interpretes
   the code like this:
*/
var y = x + f(a+b).toString();

/* The first exception to the rule is that if a line break appears after
   any of return,break,continue then JavaScript will interpret that line break
   as a semicolon. For example, if you write:
*/
return
true;

// is asummed as:
return;
true;

// however you probably meant:
return true;


/* The second exception to the rule is that operators ++ and -- are treated
   as prefix operators if no semicolon is provided.
   Consider this code, for example:
*/
x
++
y

// Is is parsed as: x; ++y;  and NOT as x++; y.
