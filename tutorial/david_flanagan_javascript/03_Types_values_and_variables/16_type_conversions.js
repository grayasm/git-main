/* Cap.3 Types, Values and Variables
   3.8 Type Conversions

   $ node 16_type_conversions.js

   JavaScript uses automatic type conversion from one type to another.
   Here is a summary of the rules

                          Converted to:
   Value                  String           Number  Boolean  Object
  +---------------------------------------------------------------------------+
   undefined              "undefined"      NaN     false    throws TypeError
   null                   "null"           0       false    throws TypeError
  +---------------------------------------------------------------------------+
   true                   "true"           1                new Boolean(true)
   false                  "false"          0                new Boolean(false)
  +---------------------------------------------------------------------------+
   "" (empty string)                       0       false    new String("")
   "1.2" (numeric)                         1.2     true     new String("1.2")
   "one" (non-numeric)                     NaN     true     new String("one")
  +---------------------------------------------------------------------------+
    0                     "0"                      false    new Number(0)
   -0                     "0"                      false    new Number(-0)
    NaN                   "NaN"                    false    new Number(NaN)
    Infinity              "Infinity"               true     new Number(Infinity)
   -Infinity              "-Infinity"              true     new Number(-Infinity)
    1 (non-zero)          "1"                      true     new Number(1)
  +---------------------------------------------------------------------------+
   {} (any object)        "[object..]"             true
   [] (empty array)       ""               0       true
   [9] (numeric elem)     "9"              9       true
   ['a'] (any array)      use join()       NaN     true
   function(){}           "function(.."    NaN     true
  +---------------------------------------------------------------------------+
*/

var a = 10 + " objects";
console.log(a);           // 10 objects

var b = "7" * "4";
console.log(b);           // 28

var c = 1 - "x";
console.log(c);           // NaN

var d = c + " objects";
console.log(d);           // NaN objects
