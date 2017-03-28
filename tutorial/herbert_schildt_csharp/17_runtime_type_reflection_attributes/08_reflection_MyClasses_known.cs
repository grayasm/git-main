/*
    The file 07_MyClasses.cs contains MyClass, which we have been using in
    the previous examples. It also adds a second class called AnotherClass
    and a third class called Demo. Thus, the assembly produced by this
    program will contain three classes.

    Next, compile this file so the file 07_MyClasses.exe is produced.
    This is the assembly that will be interrogated.
*/

/*  Locate an assembly, determine types, and create an object using
    reflection. */

using System;
using System.Reflection;


class ReflectAssemblyDemo
{
    static void Main()
    {
        int val;

        // Load the MyClasses.exe assembly.
        Assembly asm = Assembly.LoadFrom("07_MyClasses.exe");

        // Discover what types MyClasses.exe contains.
        Type[] alltypes = asm.GetTypes();
        foreach(Type temp in alltypes)
            Console.WriteLine("Found: " + temp.Name);
        Console.WriteLine();

        // Use the first type, which is MyClass in this case.
        Type t = alltypes[0]; // use first class found
        Console.WriteLine("Using: " + t.Name);

        // Obtain constructor info.
        ConstructorInfo[] ci = t.GetConstructors();
        Console.WriteLine("Available constructors: ");
        foreach(ConstructorInfo c in ci)
        {
            // Display return type and name.
            Console.Write(" " + t.Name + "(");

            // Display parameters.
            ParameterInfo[] pi = c.GetParameters();
            for(int i=0; i < pi.Length; i++)
            {
                Console.Write(pi[i].ParameterType.Name + " " + pi[i].Name);
                if(i+1 < pi.Length)
                    Console.Write(", ");
            }
            Console.WriteLine(")");
        }
        Console.WriteLine();

        // Find matching constructor.
        int x;

        for(x=0; x < ci.Length; x++)
        {
            ParameterInfo[] pi = ci[x].GetParameters();
            if(pi.Length == 2)
                break;
        }
        if(x == ci.Length)
        {
            Console.WriteLine("No matching constructor found.");
            return;
        }
        else
            Console.WriteLine("Two-parameter constructor found.\n");

        // Construct the object.
        object[] consargs = new object[2];
        consargs[0] = 10;
        consargs[1] = 20;
        object reflectOb = ci[x].Invoke(consargs);

        Console.WriteLine("\nInvoking methods on reflectOb.");
        Console.WriteLine();
        MethodInfo[] mi = t.GetMethods();

        // Invoke each method.
        foreach(MethodInfo m in mi)
        {
            // Get the parameters.
            ParameterInfo[] pi = m.GetParameters();

            if (m.Name.Equals("Set", StringComparison.Ordinal) &&
                pi[0].ParameterType == typeof(int))
            {
                // This is Set(int, int).
                object[] args = new object[2];
                args[0] = 9;
                args[1] = 18;
                m.Invoke(reflectOb, args);
            }
            else if (m.Name.Equals("Set", StringComparison.Ordinal) &&
                     pi[0].ParameterType == typeof(double))
            {
                // This is Set(double, double).
                object[] args = new object[2];
                args[0] = 1.12;
                args[1] = 23.4;
                m.Invoke(reflectOb, args);
            }
            else if (m.Name.Equals("Sum", StringComparison.Ordinal))
            {
                val = (int) m.Invoke(reflectOb, null);
                Console.WriteLine("sum is " + val);
            }
            else if (m.Name.Equals("IsBetween", StringComparison.Ordinal))
            {
                object[] args = new object[1];
                args[0] = 14;
                if((bool) m.Invoke(reflectOb, args))
                    Console.WriteLine("14 is between x and y");
            }
            else if (m.Name.Equals("Show", StringComparison.Ordinal))
            {
                m.Invoke(reflectOb, null);
            }
        }
    }
}
