==================
   Cap.7 Arrays
==================

    var a = [1, 2, 3];                // simple form
    var a = new Array(1, 2, 3);       // constructor

    var v = a[0];                     // access

    var l = a.length;                 // length property

    var a = [,,,];                    // sparse array, length=3, 3 x undefined

    var a = new Array(3);             // sparse, no elements but length=3

    var a = [1, 2, 3];
    a.length = 1;                     // deletes last 2 elements, a=[1]

    a[1] = "uno";                     // add a value
    a.push("due");                    // add a value

    var a = [1, 2, 3];
    delete a[1];                      // a= [ 1, <1 empty item>, 3 ]

    for (var i=0; i < a.length; i++)  // iterate
        var v = a[i];

    for (var i in a)                  // iterate
        var v = a[i];

    var tab = new Array(10);          // multidimensional array
    for (var i=0; i<tab.length; i++)
        tab[i] = new Array(10);

    for (var row=0; row<tab.length; row++)
        for (var col=0; col<tab[row].length; col++)
            tab[row][col] = row * col;


    var a = [1, 2, 3];                // method join()
    a.join();                         // => "1,2,3"
    a.join(" ");                      // => "1 2 3"
    a.join("");                       // => "123"

    a.reverse()                       // a=[3, 2, 1];  method reverse()

    var a = [33, 4, 1111, 222];       // method sort() works alfabetically
    a.sort();                            // a=[ 1111, 222, 33, 4]
    a.sort(function(a,b){return a-b;});  // a=[ 4, 33, 222, 1111]

    var a = [1, 2, 3];                // method concat() concatenates
    a.concat(4, 5);                   // a=[1, 2, 3, 4, 5]

    a.slice(0,3);                     // slice() returns subarray, a=[1,2,3]

    var a = [1,2,3,4,5,6,7,8];        // splice() can delete,insert,or both
    a.splice(4);                      // a=[1,2,3,4] and returns [5,6,7,8]

    var a = [];
    a.push(1,2);                      // push() append one or more elements
    a.pop();                          // a=[1] and returns 2

    a.unshift(22);                    // unshift() inserts in front, a=[22,1]
    a.shift();                        // shift() removes from front, a=[1]

    [1,2,3].toString();               // toString() => "1,2,3"

    var a = [1,2,3,4,5];              // forEach() iterates through the array
    var s=0;                          // invoking the function for each elem
    a.forEach(function(v) {s += v;}); // s = 15;

    var a = [1, 2, 3];                // map() passes each element to the
    var b = a.map(function(x){return x*x;}); // function and the result into
                                             // the returned array b=[1,4,9];

    var a = [5,4,3,2,1];              // filter() uses the predicate function
    var b = a.filter(function(x){return x<3;});  //to filter the resulted array
                                                 // b = [2, 1]

    var a = [1,2,3,4,5];
    var b = a.every(function(x){return x<10;});  // b=true, every item is < 10;
    var c = a.some(fucntion(x){return x%2===0;});// c=true, some items are even

    var a = [1,2,3,4,5];
    var sum  = a.reduce(function(x,y){return x+y;}, 0); // sum of values
    var prod = a.reduce(function(x,y){return x*y;}, 1); // product
    var max  = a.reduce(function(x,y){return x>y?x:y;});// largest value

    var a = [5,4,3,2,1,0,1];
    var b = a.indexOf(1);             // => 4
    var c = a.lastIndexOf(1);         // => 6
    var d = a.indexOf(6);             // -1, no element has value 6

    Array.isArray( [] );              // => true
    Array.isArray( {} );              // => false
