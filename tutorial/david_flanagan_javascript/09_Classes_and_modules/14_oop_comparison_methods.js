/* Cap.9 Classes and Modules
   9.6.4 The Comparison Methods

   $ node 14_oop_comparison_methods.js

   It is often useful to be able to compare two distinct objects for equality
   or even for relative order (as the < and > operators do).
*/

var Range = function Range(f, t) { this.from = f; this.to = t; }

// The Range class overwrote its constructor property. So add it now.
Range.prototype.constructor = Range;


// Order ranges by lower bound, or upper bound if the lower bounds are equal.
// Throws an error if passed a non-Range value.
// Returns 0 if and only if this.equals(that).
Range.prototype.compareTo = function(that) {
    if (!(that instanceof Range))
        throw new Error("Can't compare a Range with " + that);
    var diff = this.from - that.from;
    // Compare lower bounds
    if (diff == 0) diff = this.to - that.to; // If equal, compare upper bounds
    return diff;
};


// A Range is not equal to any nonrange.
// Two ranges are equal if and only if their endpoints are equal.
Range.prototype.equals = function(that) {
    if (that == null) return false;

    // Reject null and undefined
    if (that.constructor !== Range) return false; // Reject non-ranges

    // Now return true if and only if the two endpoints are equal.
    return this.from == that.from && this.to == that.to;
}

var a = [];
a.push(new Range(5,7));
a.push(new Range(3,5));
a.push(new Range(2,6));

a.sort( function(a,b) { return a.compareTo(b); });
