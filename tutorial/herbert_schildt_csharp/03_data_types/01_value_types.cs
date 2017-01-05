using System;

class ValueTypes
{
    static void Main()
    {
        bool    bval1 = True; // or False
        byte    bval2 = 265;  // 8bits, 0 to 255
        sbyte   sbytev= -128; // 8bits, -128 to 127
        char    cval  = 'A';
        short   shortv= 65536;  // 16bits, -32768 to 32767
        ushort  ushorv= 2;      // 16bits, 0 65535
        int     intval= 120;    // 32bits, –2,147,483,648 to 2,147,483,647
        uint    uintv = 2;      // 32bits, 0 to 4,294,967,295
        long    lval  = 122L;   // 64bits, –9,223,372,036,854,775,808 to
                                //          9,223,372,036,854,775,807
        ulong   ulongv= 2;      // 64bits, 0 to 18,446,744,073,709,551,615
        float   fval  = 3.e-6f; // single precision floating point
        double  dbval = 3.e-10; // double precision floating point
        decimal decval= 2.2;  // numeric type for financial calculations
    }
}