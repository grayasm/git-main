================================================================================
 Cap.5 Statements
================================================================================

  1. Declaration Statements
  -------------------------

     var i, j = 0, greeting = "hello " + name,
         f = function(x) { return x*x; },
         y = f(x);

     var f = function(x) { return x+1; } // assigned to a variable
     function f(x) { return x+1; }       // statement includes variable name

  2. Conditionals
  ---------------
    if (user == null) { }
    else if (user == "generic") { }
    else { }

    switch(user)
    {
        case "generic":
            console.log("generic");
            break;
        case "unknown":
            console.log("unknown");
            break;
        default:
            break;
    }


  3. Loops
  --------
      while(i < 10)
      {
          // code
          i++;
      }

      do
      {
        // code
        i++;
      }
      while(i < 10);

      for (var i = 0; i < 10; i++)
      {
        // code
      }

      for (var i in array)
      {
        console.log(array[i]);
      }


  4. Jumps
  --------
    label:
        console.log(i);
        i++;
        if (i < 10)
           continue label;

    label:
    for (var i=0; i < 10; i++)
        for (var j=0; j < 10; j++)
            for (var k=0; k < 10; k++)
                if (i == 0 && j == 0 && k == 0)
                    break label;

    function f(x)
    {
        return x*x*x + 2;
    }

    try
    {
        if (x < 0)
            throw new Error("x must be positive");
        // code
    }
    catch(e)
    {
        console.log(e);
    }
    finally
    {
        console.log("always");
    }

  5. Miscellaneous
  ----------------
    with (document.forms)
    {
        console.log(name); // aka document.forms.name
    }

    if (o === undefined) debugger; /* implementation defined breakpoint
                                      if debugger is attached
                                    */

    use strict; /* suppose to switch interpreter in stric mode of ECMAScript 5 */
