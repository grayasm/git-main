// Use dynamic with reflection.
using System;
using System.Reflection;


class DynRefDemo
{
    static void Main()
    {
        Assembly asm = Assembly.LoadFrom("15_MyClass.dll");
        Type[] all = asm.GetTypes();

        // Find the DivBy class.
        int i;
        for(i = 0; i < all.Length; i++)
            if(all[i].Name == "DivBy")
                break;

        if(i == all.Length)
        {
            Console.WriteLine("DivBy not found in assembly.");
            return;
        }

        Type t = all[i];

        // Now, find the default constructor.
        ConstructorInfo[] ci = t.GetConstructors();
        int j;
        for(j = 0; j < ci.Length; j++)
        if(ci[j].GetParameters().Length == 0)
            break;

        if(j == ci.Length)
        {
            Console.WriteLine("Default constructor not found.");
            return;
        }

        // Create a DivBy object dynamically.
        dynamic obj = ci[j].Invoke(null);

        // Now, invoke methods on obj by name. This is legal because
        // obj is of type dynamic, and the calls to the methods are

        // type-checked at runtime, not compile time.
        if(obj.IsDivBy(15, 3))
            Console.WriteLine("15 is evenly divisible by 3.");
        else
            Console.WriteLine("15 is NOT evenly divisible by 3.");

        if(obj.IsEven(9))
            Console.WriteLine("9 is even.");
        else
            Console.WriteLine("9 is NOT even.");
    }
}

