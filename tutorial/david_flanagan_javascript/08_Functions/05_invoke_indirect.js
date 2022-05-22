/* Cap.8
   8.2.4 Indirect Invocation

   $ node 05_invoke_indirect.js

   Indirect invocation can be done via 2 methods call() or apply().

   call() calls a function with a given 'this' value and arguments provided individually.
   apply() calls a function with a given 'this' value and arguments provided as an array.
*/

const person = {
  fullName: function(city, country) {
    return this.firstName + " " + this.lastName + "," + city + "," + country;
  }
}

const person1 = {
  firstName:"John",
  lastName: "Doe"
}


person.fullName.call(person1, "Oslo", "Norway");    // => John Doe,Oslo,Norway
person.fullName.apply(person1, ["Oslo", "Norway"]); // => John Doe,Oslo,Norway
