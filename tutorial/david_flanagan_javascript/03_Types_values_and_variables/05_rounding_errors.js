/* Cap.3 Types, Values and Variables
   3.1.4 Binary Floating-Point and Rounding Errors

   The IEEE-754 floating-point representation used by JavaScript is a binary
   representation, which can exactly represent fractions like 1/2, 1/8, 1/1024
   but not fractions like 1/10, 1/100 and so on.

   JavaScript numbers have plenty of precision and can approximate 0.1 very
   closely, but because it's not exact, it can lead to problems.
*/

var x = .3 - .2;    // thirty cents minus 20 cents
var y = .2 - .1;    // twenty cents minus 10 cents
x == y;             // => false: the two values are not the same
x == .1;            // => false: .3 - .2 is not equal to .1
y == .1             // => true: .2 - .1 is equal to .1
