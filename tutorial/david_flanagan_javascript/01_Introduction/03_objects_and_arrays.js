/*
  Objects & Arrays, cap.6 and 7
*/


/*
  Primitive types: numbers,  strings,  booleans
  Object types   : objects,  arrays,   functions

  JavaScript's most important data type is the object.
  An object is a collection of name/value pairs, or a string to value map.
*/
var book =
    {                          // Objects are enclosed in curly braces.
        topic: "JavaScript",   // The property "topic" has value "JavaScript".
        fat: true              // The property "fat" has value true.
    };                         // The curly brace marks the end of the object.


// Access the properties of an object with . or []:
book.topic                 // => "JavaScript"
book["fat"]                // => true: another way to access property values.
book.author = "Flanagan";  // Create new properties by assignment.
book.contents = {};        // {} is an empty object with no properties.


// JavaScript also supports Arrays (numerically indexed lists) of values:
var primes = [2, 3, 5, 7]; // An array of 4 values, delimited with [ and ].
primes[0]                  // => 2: the first element (index 0) of the array.
primes.length              // => 4: how many elements in the array.
primes[primes.length-1]    // => 7: the last element of the array
primes[4] = 9;             // Add a new element by assignment.
primes[4] = 11;            // Or alter an existing element by assignment.
var empty = [];            // [] is an empty array with no elements.
empty.length               // => 0


// Arrays and objects can hold other arrays and objects:
var points =
    [                      // An array with 2 elements.
        {x:0, y:0},        // Each element is an object.
        {x:1, y:1}
    ];


var data =
    {                             // An object with 2 properties
        trial1: [[1,2], [3,4]],   // The value of each property is an array.
        trial2: [[2,3], [4,5]]    // The elements of the arrays are arrays.
    };
