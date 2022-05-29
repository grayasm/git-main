/* Cap.9 Classes and Modules
   9.5.4 Duck-Typing

   $ node 10_identity_duck_typing.js

   None of the techniques described above for determining the class of an
   object are problem-free, at least in client-side JavaScript.
   An alternative is to sidestep the issue: instead of asking “what is the class
   of this object?” we ask instead, “what can this object do?”

   This approach to programming is common in languages like Python and Ruby and
   is called duck-typing after this expression (often attributed to poet
   James Whitcomb Riley):
       When I see a bird that walks like a duck and swims like a duck and
       quacks like a duck, I call that bird a duck.
*/


// Return true if o implements the methods specified by the remaining args.
function quacks(o /*,...*/) {
    for (var i = 1; i < arguments.length; i++) {
        var arg = arguments[i];

        // If arg is a:
        switch(typeof arg) {

            // string: check for a method with that name
        case 'string':
            if (typeof o[arg] !== "function") return false;
            continue;

            // function: use the prototype object instead
        case 'function':
            arg = arg.prototype;
            // fall through to the next case

            // object: check for matching methods
        case 'object':
            // for each property of the object
            for (var m in arg) {
                if (typeof arg[m] !== "function") continue; // skip non-methods
                if (typeof o[m] !== "function") return false;
            }
        }
    }

    // If we're still here, then o implements everything
    return true;
}

function Range(f,t) { this.from = f; this.to = f; }
Range.prototype.includes = function(x) { return this.from <= x && x <= this.to; };

function RangeEx(f,t,i) { this.from = f; this.to = t; this.i = i; }
RangeEx.prototype = Range.prototype;

// this will add reset() to Range.prototype
RangeEx.prototype.reset = function() { this.from = 0, this.to = 0, this.i = 0; };


var r = new Range(1,3);
var p = new RangeEx(1,3,0);

console.log( quacks(r, "includes") );     // => true
console.log( quacks(p, "includes") );     // => true
console.log( quacks(r, "reset") );        // => true
console.log( quacks(p, "zero") );         // => false
