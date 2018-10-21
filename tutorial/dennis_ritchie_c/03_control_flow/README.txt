.
                      Cap.3 Control Flow
                      pag.55-66

  1. an expression followed by ; becomes a statement  i++;
  2. { } groups declarations and statements into a compound statement or block
  3. if(expr) simply tests the numeric value of expr if it is non-zero
  4. the else is always associated with the closest previous else-less if
  5. switch(expr) is a multi-way decision that tests if expr matches any of
     the constant values and branches accordingly
  6. even if default is first in a switch(expr) it is ignored if a case that
     matches is found
  7. a pair of expressions separated by , is evaluated left to right with the
     type and value of the result taken from the right operand
     for (i=0, j=n; i < j; i++, j--)
         c = s[i], s[i] = s[j], s[j] = c;
  9. C provides the infinitely-abusable goto statement, and labels to branch to.
     The most common place is to break out of two or more loops at once.
         for (...) {
             for (...) {
                 if (getout)
                    goto exit;
                 ...
     exit:
        ungrab some locks;
