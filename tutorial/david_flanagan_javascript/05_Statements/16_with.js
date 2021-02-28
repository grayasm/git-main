/* Cap.5 Statements
   5.7.1 with

   $ node 16_with.js

   The with statement is used to temporarily extend the scope chain.
   It has the following syntax:

   with (object)
       statement
*/

var document = {
    forms: {
        name:"TOTAL MITYANA HIGH WAY",
        address:"Kampala Fortportal, Road, Mityana, Uganda",
        email:"info@total.ug"
    }
}

var n, a, e;

with (document.forms){
    n = name;
    a = address;
    e = email;
}

console.log("name   : ", n);
console.log("address: ", a);
console.log("email  : ", e);
/*
name   :  TOTAL MITYANA HIGH WAY
address:  Kampala Fortportal, Road, Mityana, Uganda
email  :  info@total.ug
*/
