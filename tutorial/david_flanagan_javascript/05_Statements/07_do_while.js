/* Cap.5 Statements
   5.5.2 do/while

   $ node 07_do_while.js

   The syntax is:

   do
       statement
   while(expression);
*/

function printArray(a) {
    var len = a.length, i = 0;
    if (len == 0)
        console.log("Empty Array");
    else
    {
        do {
            console.log(a[i]);
        } while(++i < len);
    }
}

printArray(['a', 'ab', 'abc']);
/*
a
ab
abc
*/
