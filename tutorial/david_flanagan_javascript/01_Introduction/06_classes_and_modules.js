/*
  1. start google-chrome
  2. type F12 and switch to console tab
  3. copy-paste this into console
  4. press Enter to run

  1.1 Core JavaScript, pag.8, a showcase for:
  Cap.9 Classes and Modules
*/

// Cap.9 is one of the longest chapters in the book. Here is a very simple
// example that demonstrates how to define a JavaScript class to represent
// 2D geometric points.

// Define a constructor function to initialize a new Point object.
function Point(x, y) {     // By convention, constructors start with capitals.
    this.x = x;            // this keyword is the new object being initialized
    this.y = y;            // Store function arguments as object properties.
}                          // No return is necessary.

// Use a constructor function with the keyword "new" to create instances.
var p = new Point(1, 1);   // The gometric point (1,1)

// Define methods for Point objects by assigning them to the prototype
// object associated with the constructor function.
Point.prototype.r = function() {
    return Math.sqrt(      // Return the square root of x^2 + y^2
        this.x * this.x +  // This is the Point object on which the method...
        this.y * this.y    // ...is invoked.
    );
};

// Now the Point object p (and all future Point objects) inherits the mothod r()
p.r()                      // => 1.414...
