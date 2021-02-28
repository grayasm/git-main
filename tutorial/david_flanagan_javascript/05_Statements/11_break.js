/* Cap.5 Statements
   5.6.2 break

   $ node 11_break.js

   The break statement, used along, causes the innermost enclosing loop or
   switch statement to exit immediately. Its syntax is simple:

   break;

   When break is used with a label, it jumps to the end of, or terminates,
   the enclosing statement that has the specified label.

   break labelname;
*/

var a = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10];

for (var i = 0; i < a.length; i++)
{
    if (a[i] == 5)
        break;

    console.log("a[", i, "]=", a[i]);
}
console.log("exit!");

/*
a[ 0 ]= 0
a[ 1 ]= 1
a[ 2 ]= 2
a[ 3 ]= 3
a[ 4 ]= 4
exit!
*/

var b = [ [1, 1, 1],
          [2, 2, 2],
          [3, 3, 3],
          [4, 4, 4],
          [5, 5, 5],
          [6, 6, 6],
          [7, 7, 7]
        ];
var c = [0, 0, 0];

compute: if (b.length > 0) {
    for (var i = 0; i < b.length; i++)
    {
        if (i == 3) break compute;

        c[0] += b[i][0];
        c[1] += b[i][1];
        c[2] += b[i][2];
    }
}

console.log("c=", c);
// c= [ 6, 6, 6 ]
