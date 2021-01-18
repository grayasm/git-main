/* Cap.4 Expressions and Operators
   4.13.3 The delete Operator

   $ node 26_the_delete_operator.js

   delete is a unary operator that attempts to:
     1. delete the object property or
     2. remove the array element specified as its operand.

   > user-defined variables declared with var statement cannot be deleted.
   > functions defined with the function statement and declared function
     parameters cannot be deleted.
*/

var o = { x:1, y:2 }
delete o.x;
console.log( "x" in o );    // false
console.log( o );           // { y:2 }

var a = [1,2,3];
delete a[2];
console.log(a.length);      // 3
console.log( a );           // [1, 2, <1 empty item> ]


var o = { x:1, y:2 };
delete o.x;                 // returns true
typeof o.x;                 // 'undefined'
delete o.x;                 // delete nonexistent property
delete o;                   // cannot delete a declared variable

delete 1;                   // argument is not lvalue
this.x = 1;                 // defines a property on global object without var
delete x;                   // try to delete it

console.log ('this.x=', this.x); // this.x=1
