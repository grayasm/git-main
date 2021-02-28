/* Cap.5 Statements
   5.7.2 debugger

   $ node 17_debugger.js

   If a debugger is attached to the program while running, then the execution
   stops and you can use the debugger to print variables values, examine the
   call stack and so on.
*/

var a = {
    x:0,
    y:0,
    z:1
}

function f(o) {
    if (o === undefined) debugger;

    // set vector to X (1,0,0)
    o.x = 1;
    o.y = 0;
    o.z = 0;
}

console.log("before vector a=", a);
f(a);
console.log("after  vector a=", a);
/*
before vector a= { x: 0, y: 0, z: 1 }
after  vector a= { x: 1, y: 0, z: 0 }
*/
