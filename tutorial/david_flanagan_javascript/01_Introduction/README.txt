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
    
    var myarr = [0, 1, 2, 3];       // "this" keyword refers to the object on
    myarr.sum = function()          // which the method is defined.
    {
        var _s = 0;
        for (var i = 0; i < this.length; i++)
            _s += this[i];
        return _s;
    }
    var s = myarr.sum();            // => 6: sum of elements.