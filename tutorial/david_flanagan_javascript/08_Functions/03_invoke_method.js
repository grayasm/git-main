/* Cap.8 Functions
   8.2.2 Method Invocation

   $ node 03_invoke_method.js

   A method is a function stored in a property of an object.
*/

var calculator = {        // An object literal
    operand1: 1,
    operand2: 1,
    add: function() {
        this.result = this.operand1 + this.operand2;
    }
};
calculator.add();         // A method invocation to compute 1+1
calculator.result;        // => 2
