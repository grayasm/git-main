/* Cap.5 Statements
   5.4.2 else if

   $ node 04_else_if.js

   else if is not really a JavaScript statement.
   It is a frequently used programming idiom that results when repeated if/else
   statements are used.
*/

var n = 10;

if (n == 1) {
    // Execute code block #1
}
else if (n == 2) {
    // Execute code block #2
}
else if (n == 3) {
    // Execute code block #3
}
else {
    // If all else fail, execute block #4
}


// of the fully nested form:
if (n == 1) {
    // Execute code block #1
}
else {
    if (n == 2) {
        // Execute code block #2
    }
    else {
        if (n == 3) {
            // Execute code block #3
        }
        else {
            // If all else fail, execute block #4
        }
    }
}
