using System;

class ValueTypes
{
    static void Main()
    {
        bool    bval1 = true; // or false
        byte    bval2 = 255;  // 8bits, 0 to 255
        sbyte   sbytev= -128; // 8bits, -128 to 127
        char    cval  = 'A';
        short   shortv= -32768;    // 16bits, -32768 to 32767
        ushort  ushorv= 65535;     // 16bits, 0 65535
        int     intval= -2147483648;  // 32bits, –2,147,483,648 to 2,147,483,647
        uint    uintv = 4294967295;   // 32bits, 0 to 4,294,967,295
        long    lval  = -9223372036854775808;
                                      // 64bits, –9,223,372,036,854,775,808 to
                                      //          9,223,372,036,854,775,807
        ulong   ulongv= 18446744073709551615;
                                      // 64bits, 0 to 18,446,744,073,709,551,615
        float   fval  = 3E-6f; // single precision floating point
        double  dbval = 3E-10; // double precision floating point
        decimal decval= 2.2m;  // numeric type for financial calculations
    }
}