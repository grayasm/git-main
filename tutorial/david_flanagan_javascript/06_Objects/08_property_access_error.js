/* Cap.6 Objects
   6.2.3 Property Access Errors

   $ node 08_property_access_error.js


   Property access expressions do not always return or set a value.
*/


// It is NOT an error to query a property that does not exists.
// If the property x is not found as an own property or an inherited property
// of o, the property access expression o.x evaluates to undefined.

book = {
    "main title": "JavaScript: The Definitive Guide"
}
console.log(book.subtitle);  // undefined: property doesn't exist



// It is an error to query a property of an object that does not exist.
try {
    var len = book.subtitle.length;
}
catch(err) {
    console.log(err);
/*  TypeError: Cannot read property 'length' of undefined
        at Object.<anonymous> (/home/mihai/Code/git-main/tutorial/david_flanagan_javascript/06_Objects/08_property_access_error.js:23:29)
        at Module._compile (internal/modules/cjs/loader.js:778:30)
        at Object.Module._extensions..js (internal/modules/cjs/loader.js:789:10)
        at Module.load (internal/modules/cjs/loader.js:653:32)
        at tryModuleLoad (internal/modules/cjs/loader.js:593:12)
        at Function.Module._load (internal/modules/cjs/loader.js:585:3)
        at Function.Module.runMain (internal/modules/cjs/loader.js:831:12)
        at startup (internal/bootstrap/node.js:283:19)
        at bootstrapNodeJSCore (internal/bootstrap/node.js:623:3)
*/
}

// Example how to guard against this kid of exception:
var len = undefined;
if (book) {
    if (book.subtitle)
        len = book.subtitle.length;
}

// A concise and idiomatic alternative to get subtitle length or undefined
var len = book && book.subtitle && book.subtitle.length;


// A property assignment fails in these circumstances:
// 1)  o has an own property p that is read-only, see definedProperty().
// 2)  o has an inherited property p that is read-only.
// 3)  o does not have an own property p, does not inherit a property p and
//     o's extensible attribute is false. In this case no new properties can
//     be defined on it.
