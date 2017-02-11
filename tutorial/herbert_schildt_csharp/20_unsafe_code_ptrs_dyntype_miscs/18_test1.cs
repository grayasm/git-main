using System;


namespace MyNS
{
    public class MyClass
    {
        public MyClass()
        {
            Console.WriteLine("Constructing from MyClass1.dll.");
        }
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
