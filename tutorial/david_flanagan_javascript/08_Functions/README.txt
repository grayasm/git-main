========================
   Cap.8 Functions
========================


var f = function(x,y) { return x+y; }           // define a function
f(2,3);                                         // invoke a function

(function(x,y) { return x+y; }(2,3));           // define and invoke a function


var a = {
    r: 0,
    f: function(x,y) { this.r = x+y; }          // define a method
    };
a.f(2,3);                                       // invoke a method


const a = {
    f: function(x,y) { this.r = x+y; }
    };
var b = { r:0 };                                // indirect invocation
a.f.call(b, 2, 3);                              // invoke a.f as part of b obj
a.f.apply(b, [2, 3]);                           // invoke a.f as part of b obj


var f = function(x, /*optional*/ y){            // optional argument
    if (y === undefined) y = 0;
    ...
}


function max(/*...*/){                          // variable number of arguments
    for(var i=0; i<arguments.length; i++)       // Function's Arguments object
        if (arguments[i] !== undefined) { }     // arguments is 0 index based
}


var f = function(a) { a.r = a.x + a.y; }        // function accepts an object
f({r:0, x:10, y:2})                             // calling f with an object


function add(x,y) { return x+y; }               // assign a func to a variable
function op(op, ls, rs) { return op(ls, rs); }
var i = op(add, 2, 3);


var f.count = 0;                                // count is a f's property
function f() { return f.count++; }


(function(){                                    // function as a namespace can
    function f(x){                              // contain an entire module
        if(x < 1) return 1;
        else return x*f(x-1);
        }
    var f5 = f(5);
    }());


var inc = (function(){                          // closure is a function+scope
    var cnt = 0;                                // private variable 'cnt' is not
    return function() { return cnt++; };        // accessible outside returned
    }());                                       // anonymous function
inc();  // 0
inc();  // 1


function f(y) { return this.x+y; }
var o = {x:1}
var f2 = f.bind(o);                             // use Function.bind() to bind
f2(2);  // 3                                    // f to o


function sum(a,b) { return a+b; }               // Function.toString() returns
sum.toString();                                 // 'function sum(a,b) { return a+b; }'



function not(f){                                // a higher-order function
    return function(){                          // is a function that operates
        return !f.apply(this,arguments);        // on functions
        };
        }
var even = function(x) { return x%2 == 0; }
var odd = not(even);
[1,1,3,5,5].every(odd); // true
