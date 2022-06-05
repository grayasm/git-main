   N3337 page 30
   2.14.8 User-defined literals   [lex.ext]

   user-defined-literal:
        user-defined-integer-literal
        user-defined-floating-literal
        user-defined-string-literal
        user-defined-character-literal

   user-defined-integer-literal:
        decimal-literal ud-suffix
        octal-literal ud-suffix
        hexadecimal-literal ud-suffix

   user-defined-floating-literal:
        fractional-constant exponent-part opt ud-suffix
        digit-sequence exponent-part ud-suffix

   user-defined-string-literal:
        string-literal ud-suffix

   user-defined-character-literal:
        character-literal ud-suffix

   ud-suffix:
        identifier