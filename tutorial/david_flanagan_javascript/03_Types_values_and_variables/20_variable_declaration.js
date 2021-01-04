/* Cap.3 Types, Values and Variables
   3.9 Variable Declaration

   $ node 20_variable_declaration.js
*/


/*    declare a variable using var    */
var a;
var b;
var c, d;

/*    combine declaration with initialization    */
var m = "hello";
var i = 0, j = 0, k = 0;


/*    declare a variable as part of the for/in loop    */
for(var i = 0; i < 5; i++)             console.log("i=", i);
for(var i = 0, j = 5; i < 5; i++, j--) console.log("i=", i, " j=", j);
var o = [2,null,4,6,8,10]
for(var p in o) console.log("p in o", o, "=", o[p]);


/*    declare a variable more than once with var statement    */
var i = 0; console.log("i=", i);    // 0
var i = -5;console.log("i=", i);    //-5

