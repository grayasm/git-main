/*
    There are some restrictions to overloading operators. You cannot alter the
    precedence of any operator. You cannot alter the number of operands required
    by the operator, although your operator method could choose to ignore an
    operand. There are several operators that you cannot overload.

    Perhaps most significantly, you cannot overload any assignment operator,
    including the compound assignments, such as +=. Here are the other operators
    that cannot be overloaded.
    This list includes several operators that are discussed later in this book.

    &&        ( )        .        ?
    ??        [ ]        ||       =
    =>        ->         as       checked
    default   is         new      sizeof
    typeof    unchecked
*/

using System;
class Example { static void Main() {} }
