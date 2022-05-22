/* Cap.8
   8.7.3 The call() and apply() Methods

   $ node 16_method_call_and_apply.js

   call() and apply() allow you to indirectly invoke a function as if it were a
   method of some other object.

   The diference between them is:
   call() method takes arguments separately
   apply() method takes arguments as an array
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
