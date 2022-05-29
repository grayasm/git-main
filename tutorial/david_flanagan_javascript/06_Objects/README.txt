================================================================================
 Cap.6 Objects
================================================================================

    JavaScript fundamental datatype is the object:
    ----------------------------------------------
    var book = {
        "main title": "JavaScript",
        "for":        "all audiences",
        author: {
           firstname: "David",
           surname:   "Flanagan"
        }
    };

    Create and initialize an object with new operator:
    -------------------------------------------------
    var date = new Date();

    Create and initialize an object with Object.create() method:
    -----------------------------------------------------------
    var point = Object.create( {x:1, y:2} );

    Set and get a property by using dot (.) or square braket ([]) operator:
    ----------------------------------------------------------------------
    var title = book["main title"];
    book["main title"] = "JavaScript ECMAScript edition";

    Object as associative arrays:
    ----------------------------
    customer = {
            address0: "Millaray Nanuk",
            address1: "1334 3RD STREET PROMENADE#304",
            address2: "SANTA MONICA CA 90401-1336",
            address3: "UNITED STATES OF AMERICA"
    };
    var addr = ""
    for (i = 0; i < 4; i++)
        addr += customer["address" + i] + '\n';


    Object inheritance:
    ------------------
    var o1 = { x:100 };
    var o2 = Object.create(o1);
    console.log(o2.x);         // o2 contains x:100 property

    The inheritance is done via base object prototype concept:
    o1.isPrototypeOf(o2);                   // true
    Object.prototype.isPrototypeOf(o2);     // true


    Add and delete a property:
    ------------------------
    book.ISBN = "978-0-13-601970-1";
    delete book.ISBN;

    Test if a property exists:
    -------------------------
    if ("ISBN" in book) { ... }
    if (book.hasOwnProperty("ISBN")) { ... }

    Enumerate all properties (own and inherited):
    --------------------------------------------
    for(prop in book) {
            if (book.hasOwnProperty(prop)) { ... } // own property
            else { ... }                           // inherited property
    }

    Object accessors aks getters and setters:
    ----------------------------------------
    var o = {
            x : 0,
            get value() { return this.x; },
            set value(v) { this.x = v;   }
    };
    console.log("value is " + o.value); // calls get
    o.value = 20;                       // calls set


    Object properties are (a) Writeable, (b) Enumerable and (c) Configurable:
    ------------------------------------------------------------------------
    var o = {x:1}
    Object.getOwnPropertyDescriptor(o, "x");  // will return
    // { value: 1, writeable: true, enumerable: true, configurable: true }

    equivalent with:
    Object.defineProperty(o, "x", { value:1,
                                    writeable: true,
                                    enumerable: true,
                                    configurable: true });

    Object class attribute, returned by toString():
    ---------------------------------------------
    var v = []
    Object.prototype.toString.call(v);                // [object Array]
    Object.prototype.toString.call({});               // [object Object]
    Object.prototype.toString.call(1.1);              // [object Number]
    Object.prototype.toString.call(1.1).slice(8, -1); // Number


    Object.seal(..) - you cannot add new properties
    ------------------------------------------------
    var o = Object.seal( { x:0 } );
    o.y = 200;
    console.log(o.y);   // undefined (it cannot be added)


    Object.freeze(..) - you cannot change a property anymore
    --------------------------------------------------------
    var o = Object.freeze( { x:0 } );
    o.x = 200;
    console.log(o.x);   // 0  (it cannot be modified anymore)


    Serialize with JSON.stringify() and deserialize with JSON.parse():
    -----------------------------------------------------------------
    var o = { x:1, y: {z: [false, null, ""] } };
    s = JSON.stringify(o);
    p = JSON.parse(s);

    // p object is a recreation of o;
