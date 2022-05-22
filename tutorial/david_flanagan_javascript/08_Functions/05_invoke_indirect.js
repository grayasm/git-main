/* Cap.8
   8.2.4 Indirect Invocation

   $ node 05_invoke_indirect.js

   Indirect invocation can be done via 2 methods call() or apply().
*/

const person = {
    fullName: function() {
        return this.firstName + " " + this.lastName;
    }
}
const person1 = {
    firstName: "John",
    lastName: "Doe"
}

// This will return "John Doe":
person.fullName.call(person1);
