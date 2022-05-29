/* Cap.9 Classes and Modules
   9.6.1 Example: A Set Class

   $ node 11_oop_a_set_class.js

   In this section we switch gears and demonstrate a number of practical
   techniques for programming with JavaScript classes. We begin with two
   nontrivial example classes that are interesting in their own right but
   also serve as starting points for the discussions that follow.
*/


// A set as an unordered collection of values, with no duplicates.

function Set() {                       // This is the constructor
    this.values = {};                  // The properties hold the set
    this.n = 0;                        // How many values are in the set
    this.add.apply(this, arguments);   // All arguments are values to add
};

Set.prototype.add = function() {
    for (var i = 0; i < arguments.length; i++) {   // For each argument
        var val = arguments[i];                    // The value to add
        var str = Set._v2s(val);                   // Transform it to a string
        if (!this.values.hasOwnProperty(str)) {    // If not already in the set
            this.values[str] = val;                // Map string to value
            this.n++;                              // Increase set size
        }
    }
    return this;                                   // Support chained calls
};

Set.prototype.remove = function() {
    for (var i = 0; i < arguments.length; i++) {   // For each argument
        var str = Set._v2s(arguments[i]);          // Map to a string
        if (this.values.hasOwnProperty(str)) {     // If it is in the set
            delete this.values[str];               // Delete it
            this.n--;                              // Decrease set size
        }
    }
    return this;                                   // For method chaining
};

// Return true if the set contains value; false otherwise.
Set.prototype.contains = function(value) {
    return this.values.hasOwnPrototype(Set._v2s(value));
};

Set.prototype.size = function() { return this.n; };

// Call function f on the specified context for each element of the set.
Set.prototype.foreach = function(f, context) {
    for (var s in this.values)                     // For each string in the set
        if (this.values.hasOwnProperty(s))         // Ignore inherited properties
            f.call(context, this.values[s]);       // Call f on the value
};


// This internal function maps any JavaScript value to a unique string.
Set._v2s = function(val) {
    switch(val) {
    case undefined:     return 'u';                // Special primitive
    case null:          return 'n';                // values get single-letter
    case true:          return 't';                // codes.
    case false:         return 'f';
    default: switch(typeof val) {
        case 'number':  return '#' + val;          // Numbers get # prefix.
        case 'string':  return '"' + val;          // Strings get " prefix.
        default: return '@' + objectId(val);       // Objects and funcs get @
    }
    }

    /* For any object, return a string. This function will return a different
       string for different objects, and will always return the same string
       if called multiple times for the same object. To do this it creates a
       property on o. In ES5 the property would be nonenumerable and read-only.
    */
    function objectId(o) {
        var prop = "|**objectId**|";               // Private prop name for ids
        if (!o.hasOwnProperty(prop))               // If the object has no id
            o[prop] = Set._v2s.next++;             // Assign it the next avail
        return o[prop];                            // Return the id
    }
};

Set._v2s.next = 100;   // Start assigning object ids at this value.


// Let's try to see how to use the class Set()
var s = new Set(1,1,1,1,   2,2,2,2,   3,3,3,3,   4,4,4,4);

console.log( s.size() );  // => 4
