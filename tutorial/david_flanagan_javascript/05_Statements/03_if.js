/* Cap.5 Statements
   5.4.1 if

   $ node 03_if.js

   The if statement has two forms:

   if (expression)
       statement

   if (expression)
       statement1
   else
       statement2
*/

var username, address, n;

if (username == null)
    username = "John Doe";

if (!username)
    username = "John Doe";

if (!address) {
    address = "";
    message = "Please specify a mailing address.";
}

if (n == 1)
    console.log("You have 1 new message.");
else
    console.log("You have " + n + " new messages.");


// Nested if statements with else clauses.
i = j = 1;
k = 2;
if (i == j)
    if (j == k)
        console.log("i equals k");
else
    console.log("i doesn't equal j");       // WRONG!!


// Correct identation
if (i == j){
    if (j == k)
        console.log("i equals k");
    else
        console.log("i doesn't equal j");   // OOPS!
}

// Using curly braces to make the if statement less ambiguous.
if (i == j) {
    if (j == k) {
        console.log("i equals k");
    }
}
else {
    console.log("i doesn't equal j");
}
