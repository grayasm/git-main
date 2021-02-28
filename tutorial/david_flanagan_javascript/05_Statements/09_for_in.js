/* Cap.5 Statements
   5.5.4 for/in

   $ node 09_for_in.js

   A for/in loop looks like this:

   for (variable in object)
       statement
*/


var o = [0, '0', {x:0}, "zero"]
for(var p in o)
    console.log('p=', p, ' o[p]=', o[p] );

/*
p= 0   o[p]= 0
p= 1   o[p]= 0
p= 2   o[p]= { x: 0 }
p= 3   o[p]= zero
*/

var o = {x:1, y:2, z:3};
var a = [], i = 0;
for(a[i++] in o) /* empty */;

console.log(a);
// [ 'x', 'y', 'z' ]


for(var i in o)
    console.log('i=', i, ' o[i]=', o[i]);
/*
i= x  o[i]= 1
i= y  o[i]= 2
i= z  o[i]= 3
*/
