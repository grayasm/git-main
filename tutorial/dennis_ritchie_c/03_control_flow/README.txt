.
                      Cap.3 Control Flow
                      pag.55-66

  1. an expression followed by ; becomes and expression
  2. { } groups declarations and statements into a compound statement or block
  3. if(expr) evaluates if expr is true - that is has a non-zero value
  4. switch(expr) is a multi-way decision that tests if expr matches any of
     the constant values and branches accordingly
  5. even if default is first in a switch(expr) it is ignored if a case that
     matches is found
  6. loops while and for:
     for(expr1; expr2; expr3) statement  /* is equivalent with: */
     expr1; while(expr2) { statement; expr3; }
  7. loops do-while: do { statement; } while(expr);
  8. goto statement and labels are used to branch to
     the most common use case is to abandon processing in a deeply nested
     structure, such as breaking out of two or more loops at once.
