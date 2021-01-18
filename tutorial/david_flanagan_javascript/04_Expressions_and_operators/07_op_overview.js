/* Cap.4 Expressions and Operators
   4.7 Operator Overview

   $ node 07_op_overview.js

   Operators are represented by:
   - punctuation characters such as + and =
   - keywords such as delete and instanceof

   Column A gives the operator associativity: L (left-to-right), R (right-to-left)
   Column N gives the number of operands

   Operator       Operation                        A  N   Types
  +-------------------------------------------------------------------------+
   ++             Pre-or post-increment            R  1   lval->num
   --             Pre-or post-decrement            R  1   lval->num
   -              Negate number                    R  1   num->num
   +              Convert to number                R  1   num->num
   ~              Invert bits                      R  1   int->int
   !              Invert boolean value             R  1   bool->bool
   delete         Remove a property                R  1   lval->bool
   typeof         Determine type of operand        R  1   any->str
   void           Return undefined value           R  1   any->undef
  +-------------------------------------------------------------------------+
   * / %          Multiply divide remainder        L  2   num,num->num
  +-------------------------------------------------------------------------+
   + -            Add substract                    L  2   num,num->num
   +              Concatenate strings              L  2   str,str->str
  +-------------------------------------------------------------------------+
   <<             Shift left                       L  2   int,int->int
   >>             Shift right with sign extension  L  2   int,int->int
   >>>            Shift right with zero extension  L  2   int,int->int
  +-------------------------------------------------------------------------+
   < <= > >=      Compare in numeric order         L  2   num,num->bool
   < <= > >=      Compare in alphabetic order      L  2   str,str->bool
   instanceof     Test object class                L  2   obj,func->bool
   in             Test whether property exists     L  2   str,obj->bool
  +-------------------------------------------------------------------------+
   ==             Test for equality                L  2   any,any->bool
   !=             Test for inequality              L  2   any,any->bool
   ===            Test for strict equality         L  2   any,any->bool
   !==            Test for string inequality       L  2   any,any->bool
  +-------------------------------------------------------------------------+
   &              Compute bitwise AND              L  2   int,int->int
   ^              Compute bitwise XOR              L  2   int,int->int
   |              Compute bitwise OR               L  2   int,int->int
  +-------------------------------------------------------------------------+
   &&             Compute logical AND              L  2   any,any->any
   ||             Compute logica OR                L  2   any,any->any
   ?:             Choose 2nd or 3rd operand        R  3   bool,any,any->any
  +-------------------------------------------------------------------------+
   =              Assign to a variable a property  R  2   lval,any->any
   *= /= %= +=    Operate and assign               R  2   lval,any->any
   -= &= ^= |=
   <<= >>= >>>=
  +-------------------------------------------------------------------------+
   ,           Discard 1st operand, return second  L  2   any,any->any
  +-------------------------------------------------------------------------+


   4.7.1 Number of Operands
   - binary operator
   - unary operator
   - ternary operator

   4.7.2 Operand and Result Type
   - operators usually convert the type of their operands as needed
   - every JavaScript value is either "truthy" or "falsy"

   4.7.3 Lvalues
   - the assignment operand and few others expect an operand of type lval.
   - lvalue is a historical term that means "an expression that can legally
     appear on the (l)LEFT side of an assignment expression".

   4.7.4 Operator Side Effects
   - increment and decrement operators ++ -- perform an implicit assignment
   - delete operator has side effect of assigning undefined to the property
*/
