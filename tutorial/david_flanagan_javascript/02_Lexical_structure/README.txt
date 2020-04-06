===============================================================================
                   Cap.2 Lexical Structure
===============================================================================
  1) Escape a Unicode character with \u followed by 4 hexadecimal digits.
  2) "café" === "caf\u00e9"
  3) // This is a single-line comment.
  4) /* This is a multi-line comment. */
  5) Non-English variable names are allowed:
     var sí = true;
     var π = 3.14;
  6) Keywords reserved in JavaScript:
     break        delete        function        return        typeof
     case         do            if              switch        var
     catch        else          in              this          void
     continue     false         instanceof      throw         while
     debugger     finally       new             true          with
     default      for           null            try

  7) ECMAScript5 reserves the following words:
     class        const         enum            export        extends
     import       super

  8) This words are reserved in strict mode:
     implements   let           private         public        yield
     interface    package       protected       static        arguments
     eval

  9) ECMAScript3 reserved all Java keywords:
     abstract     double        goto            native        static
     boolean      enum          implements      package       super
     byte         export        import          private       synchronized
     char         extends       int             protected     throws
     class        final         interface       public        transient
     const        float         long            short         volatile

 10) JavaScript global variables and functions:
     arguments    encodeURI           Infinity  Number            RegExp
     Array        encodeURIComponent  isFinite  Object            String
     Boolean      Error               isNaN     parseFloat        SyntaxError
     Date         eval                JSON      parseInt          TypeError
     EvalError    decodeURI           Math      RangeError        undefined
     Function     decodeURIComponent  NaN       ReferenceError    URIError

 11) Use semicolons to remove uncertainity for multiline statements:
     var y = x + f
     (a+b).toString()    // can also be interpreted as

     var y = x + f(a+b).toString();

 12) Another exception involves ++ and -- operators. Again, use semicolons.
     x
     ++
     y                  // is parsed as x; ++y;
================================================================================
