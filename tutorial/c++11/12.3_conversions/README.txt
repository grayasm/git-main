    N3337 page 248
    12.3.2  Conversion functions [class.conv.fct]

    A member function of a class X having no parameters with a name of the form

        conversion-function-id:
            operator conversion-type-id

        conversion-type-id:
            type-specifier-seq conversion-declarator opt

        conversion-declarator:
            ptr-operator conversion-declarator opt

   specifies a conversion from X to the type specified by the conversion-type-id.
   Such functions are called conversion functions.
   No return type can be specified.
