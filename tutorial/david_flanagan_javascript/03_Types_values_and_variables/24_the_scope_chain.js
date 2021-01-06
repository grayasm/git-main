/* Cap.3 Types, Values and Variables
   3.10.3 The Scope Chain

   This notion of a scope chain is helpful for understading 'with' statement
   and closures.

   1) When a function is defined, it stores the scrope chain then in effect.
   2) When that function is invoked, it creates a new object to store its
      local variables, and adds that new object to the stored chain to create
      a new longer chain that represents teh scope for that function invocation.
   3) Each time an outer function is called, the nested function is defined again.
      On each invocation of the outer function the nested function scope chain
      will be different.
*/

function test() {
    console.log("1) i=", i);                 // i= 101

    i = 200;

    console.log("2) i=", i);                 // i= 200

    delete i;

    try
    {
        console.log("3) i=", i);
    }
    catch(e)
    {
        console.log("3) exception");         // exception
    }
}

i = 101;
test();
