// extern alias statements must be at the top of the file.
extern alias Asm1;
extern alias Asm2;


using System;


class Demo
{
    static void Main()
    {
        Asm1::MyNS.MyClass t = new Asm1::MyNS.MyClass();
        Asm2::MyNS.MyClass t2 = new Asm2::MyNS.MyClass();
    }
}


/*
    Start by compiling test1.cs and test2.cs into DLLs.
    This can be done easily from the command line by using these commands:

csc /t:library test1.cs
csc /t:library test2.cs

    Next, compile test3.cs by using this command line:

csc /r:Asm1=test1.dll /r:Asm2=test2.dll test3.cs
*/
