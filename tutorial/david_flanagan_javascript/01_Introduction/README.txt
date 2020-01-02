===============================================================================
                   Cap.1 Introduction to JavaScript
===============================================================================
  1) F12: in a browser will open the debugging console.
  2) JavaScript is highlevel, dynamic, untyped interpreted programming language.
  3) Standardized by ECMA - the European Computer Manufacturer's Association.
  4) Due to trademark issues it's name is ECMAScript.
  5) Core JavaScript:

    // single line comment
    /* multiple line comment */
    var x = 1;                 // all numbers are 64bit floating point
    var x = 0.01;
    var x = "hello world";     // String
    var x = 'JavaScript';      // Also a string
    var x = true;              // Boolean value.
    var x = false;             // The other boolean value.
    var x = null;              // Special value that means "no value".
    var x = undefined;         // Like null.

    var book =                 // An object.
    {
        topic: "java",
        price: 12.2
    };

    book.topic = "JavaScript";      // Change the property values.
    book.author = "Flanagan";       // Create a new property by assignment.
    book.contents = { };            // An empty object with no properties.

    var primes = [2, 3, 5, 7];      // An Array
    primes[0];                      // => 2: the first element.
    primes.length;                  // => 4: how many elements in the array.
    primes[primes.length-1];        // => 7: the last element of the array.
    primes[4] = 9;                  // Add a new element by assignment.
    primes[4] = 11;                 // Alter an existing element by assignment.

    var empty = [];                 // An empty array.

    var points =                    // Arrays and objects can hold other
    [                               // arrays and objects.
        {x:0, y:0},
        {x:1, y:1}
    ];

    var data =
    {
        prop1: [[1,2], [3,4]],
        prop2: [[2,3], [4,5]]
    };

    // Arithmetic operators:    +  -  *  /  ++  --  +=  -=  *=  /=
    // Relational operators:    <  <=  ==  ===  !=  !==  >  >=
    // Logical operators   :    &&  ||  !()

    function plus1(x)               // Function block.
    {
        return x + 1;
    }

    var square = function(x)        // Functions are values & can be assgigned.
    {
        return x * x;
    };

    square(4);                      // => 16: invoke a function

    points.dist = function()
    {                               // "this" keyword is the points array.
        var p1 = this[0];           // First element of the array.
        var p2 = this[1];           // Second element of the array.
        var dx = p2.x - p1.x;
        var dy = p2.y - p1.y;
        return Math.sqrt(dx*dx + dy*dy);
    }
    points.dist();                  // => 1.414: distance between the 2 points.

    // JavaScript control structure elements: if, while, for, do/while
    function abs(x)
    {
        if (x > 0) return x;
        else return -x;
    }

    function factorial(n)
    {
        var prod = 1;
        while(n > 1)
        {
            product *= n;
            n--;
        }
        return prod;
    }

    function factorial(n)
    {
        var i, prod = 1;
        for (i = 2; i <= n; i++)
        {
            prod *= i;
        }
        return prod;
    }
