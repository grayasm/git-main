/* Cap.4 Expressions and Operators
   4.13.5 The Comma Operator (,)

   $ node 28_the_comma_operator.js

   The comma (,) operator is binary.
   It evaluate its left operand, then its right operand, then retuns the value
   of the right operand.
*/


i=0, j=1, k=2;      // is equivalent with
i=0; j=1; k=2;


// The only situation in which the comma operator is commonly used is with
// a for loop, that has multiple loop variables:

for(var i=0, j=10; i < j; i++, j--)
    console.log('i=', i, ' j=', j);

/*
i= 0  j= 10
i= 1  j= 9
i= 2  j= 8
i= 3  j= 7
i= 4  j= 6
*/
