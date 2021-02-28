/* Cap.5 Statements
   5.6.3 continue

   $ node 12_continue.js

   Continue restarts a loop at the next iteration.
   continue;
   continue labelname;
*/


var a = [0, 1, null, null, 4];

for(var i = 0; i < a.length; ++i)
{
    if (!a[i]) continue;

    console.log('a[', i, ']=', a[i]);
}
console.log("exit!");
/*
a[ 1 ]= 1
a[ 4 ]= 4
exit!
*/
