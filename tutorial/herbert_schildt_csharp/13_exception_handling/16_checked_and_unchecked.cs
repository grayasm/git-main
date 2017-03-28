/*
    Using checked and unchecked
    A special feature in C# relates to the generation of overflow exceptions
    in arithmetic computations. As you know, it is possible for some types
    of arithmetic computations to produce a result that exceeds the range
    of the data type involved in the computation. When this occurs, the result
    is said to overflow. For example, consider the following sequence:

byte a, b, result;
a = 127;
b = 127;
result = (byte)(a * b);

    Here, the product of a and b exceeds the range of a byte value. Thus,
    the result overflows the type of the result.
    C# allows you to specify whether your code will raise an exception
    when overflow occurs by using the keywords checked and unchecked.
    To specify that an expression be checked for overflow, use checked.
    To specify that overflow be ignored, use unchecked.
    In this case, the result is truncated to fit into the target type of
    the expression.

    The checked keyword has these two general forms. One checks a specific
    expression and is called the operator form of checked. The other checks
    a block of statements and is called the statement form.

checked (expr)
checked {
    // statements to be checked
}


    Here, expr is the expression being checked. If a checked expression
    overflows, then an OverflowException is thrown.
    The unchecked keyword also has two general forms. The first is the
    operator form, which ignores overflow for a specific expression.
    The second ignores overflow for a block of statements.

unchecked (expr)
unchecked {
    // statements for which overfl ow is ignored
}

    Here, expr is the expression that is not being checked for overflow.
    If an unchecked expression overflows, then truncation will occur.
*/

using System;

class CheckedDemo
{
    static void Main()
    {
        byte a, b;

        byte result;
        a = 127;
        b = 127;

        try
        {
            result = unchecked((byte)(a * b));
            Console.WriteLine("Unchecked result: " + result);

            result = checked((byte)(a * b)); // this causes exception
            Console.WriteLine("Checked result: " + result); // won't execute
        }
        catch (OverflowException exc)
        {
            Console.WriteLine(exc);
        }
    }
}
