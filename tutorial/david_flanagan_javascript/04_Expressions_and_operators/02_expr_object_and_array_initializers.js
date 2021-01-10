/* Cap.4 Expressions and Operators
   4.2 Object and Array Initializers

   $ node 02_expr_object_and_array_initializers.js

   The initializer expressions are called:
   1) object literals  and,
   2) array literals


   1) Object Initializer:
      - comma-separated list of expressions contained within curly {} brakets.
      - each subexpression is prefixed with a property name and a collon x:2.3
      - object literals can be nested { upperLeft: {x:2,y:2}, .. }
      - property names can also be strings { "upperLeft": {x:2,y:2}, .. }

   2) Array Initializer:
      - comma-separated list of expressions contained within square [] brakets.
      - undefined elements can be included in an array literal [1,,,,,5]
*/


var i = []              // An empty array
var i = [1+2, 3+4]      // A 2-element array.

console.log(i);         // [ 3, 7 ]

var matrix = [[1,2,3], [4,5,6], [7,8,9]];
var sparse = [1,,,,,5];

console.log(matrix);    // [ [ 1, 2, 3 ], [ 4, 5, 6 ], [ 7, 8, 9 ] ]
console.log(sparse);    // [ 1, <4 empty items>, 5 ]


var p = { x:2.3, y:-1.2 };    // An object with 2 properties
var q = {};                   // An empty object with no properties
q.x = 2.3;                    // Now q has the same properties as p
q.y = -1.2;

console.log(p);               // { x: 2.3, y: -1.2 }
console.log(q);               // { x: 2.3, y: -1.2 }

var rectangle = { upperLeft:  { x:2, y:2 },
                  lowerRight: { x:4, y:5 }};
console.log(rectangle);       // { upperLeft: { x: 2, y: 2 }, lowerRight: { x: 4, y: 5 } }


var side = 1;
var square = { "upperLeft":  {x:p.x, y:p.y},
               'lowerRight': {x:p.x + side, y:p.y + side}};
console.log(square);
/*
{
  upperLeft: { x: 2.3, y: -1.2 },
  lowerRight: { x: 3.3, y: -0.19999999999999996 }
}
*/
