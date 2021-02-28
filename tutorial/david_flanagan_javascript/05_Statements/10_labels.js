/* Cap.5 Statements
   5.6.1 Labeled Statements

   $ node 10_labels.js

   Any statement may be labeled by preceding it with an identifier and a colon

   identifier: statement
*/

var arr = [0, 1, 2, 3, 4, 5]
var i = 0;

mainloop: while(arr[i] != null)
{
    console.log("arr[", i, "]=", arr[i]);
    i++
    continue mainloop;
}

console.log("exit!");

/*
arr[ 0 ]= 0
arr[ 1 ]= 1
arr[ 2 ]= 2
arr[ 3 ]= 3
arr[ 4 ]= 4
arr[ 5 ]= 5
exit!
*/
