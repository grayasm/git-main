/* Header     : core
   Signature  : alignas (expression)
                alignas (type-id)
                alignas (pack...)
   Description:
      the alignas specifier may be applied to the declaration of a variable or
      a non-bitfield class data member, or it can be applied to the declaration
      of definition of a class/struct/union or enumeration. It cannot be applied
      to a function parameter or to the exception parameter of a catch clause.

      The object or the type declared by such a declaration will have its
      alignment requirement equal to the strictest (largest) non-zero expression
      of all alignas specifiers used in the declaration, unless it would weaken
      the natural alignment of the type.

      If the strictest (largest) alignas on a declaration is weaker than the
      alignment it would have without any alignas specifiers (that is, weaker
      than its natural alignment or weaker than alignas on another declaration
      of the same object or type), the program is ill-formed:

      struct alignas(8) S {};
      struct alignas(1) U { S s; }; --> error: alignment of U would have been 8
                                               without alignas(1)

      
 */
int main()
{
	return 0;
}
