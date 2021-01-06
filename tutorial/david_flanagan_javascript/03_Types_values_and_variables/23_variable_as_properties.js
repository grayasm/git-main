/* Cap.3 Types, Values and Variables
   3.10.2 Variables As Properties

   - a global variable is a property of the global object
   - (1) If you use 'var' to declare the variable, the property that is created
         is nonconfigurable, which means it cannot be deleted with the
         'delete' operator.
   - (2) If you're not using strict mode and you assign a value to a undeclared
         variable, JavaScript automatically creates a global variable for you.
         Variables created this way are regular, configurable properties of
         the global object and they can be deleted.
*/


var truevar = 1;          // A property declared global variable, nondeletable.
fakevar = 2;              // Creates a deletable property of the global object.
this.fakevar2 = 3;        // This does the same thing.

delete truevar;           // => false: variable not deleted
delete fakevar;           // => true:  variable deleted
delete this.fakevar2;     // => true:  variable deleted

console.log('truevar=', truevar);
try {
    console.log('fakevar=', fakevar);
} catch(e) {
    console.log('fakevar exception');
}

try {
    console.log('this.fakevar2=', this.fakevar2);
} catch(e) {
    console.log('this.fakevar2 exception');
}


/* output:
truevar= 1
fakevar exception
this.fakevar2= undefined
*/
