/*
    Fully Automating Type Discovery

     Even though the preceding program was able to fully use MyClass
     without explicitly specifying MyClass in the program, it still
     relied upon prior knowledge of the contents of MyClass. For example,
     the program knew the names of its methods, such as Set and Sum.

     However, using reflection it is possible to utilize a type about
     which you have no prior knowledge. To do this, you must discover
     all information necessary to construct an object and to generate
     method calls.
*/


// Utilize MyClass without assuming any prior knowledge.

using System;
using System.Reflection;


class ReflectAssemblyDemo
{
    static void Main()
    {
        int val;
        Assembly asm = Assembly.LoadFrom("07_MyClasses.exe");
        Type[] alltypes = asm.GetTypes();
        Type t = alltypes[0]; // use first class found
        Console.WriteLine("Using: " + t.Name);
        ConstructorInfo[] ci = t.GetConstructors();

        // Use first constructor found.
        ParameterInfo[] cpi = ci[0].GetParameters();
        object reflectOb;
        if(cpi.Length > 0)
        {
            object[] consargs = new object[cpi.Length];

            // Initialize args.
            for(int n=0; n < cpi.Length; n++)
                consargs[n] = 10 + n * 20;

            // Construct the object.
            reflectOb = ci[0].Invoke(consargs);
        }
        else
            reflectOb = ci[0].Invoke(null);

        Console.WriteLine("\nInvoking methods on reflectOb.");
        Console.WriteLine();

        // Ignore inherited methods.
        MethodInfo[] mi = t.GetMethods(BindingFlags.DeclaredOnly |
                                       BindingFlags.Instance |
                                       BindingFlags.Public) ;

        // Invoke each method.
        foreach(MethodInfo m in mi)
        {
            Console.WriteLine("Calling {0} ", m.Name);

            // Get the parameters.
            ParameterInfo[] pi = m.GetParameters();

            // Execute methods.
            switch(pi.Length)
            {
                case 0: // no args
                    if(m.ReturnType == typeof(int))
                    {
                        val = (int) m.Invoke(reflectOb, null);
                        Console.WriteLine("Result is " + val);
                    }
                    else if(m.ReturnType == typeof(void))
                    {
                        m.Invoke(reflectOb, null);
                    }
                    break;

                case 1: // one arg
                    if(pi[0].ParameterType == typeof(int))
                    {
                        object[] args = new object[1];
                        args[0] = 14;
                        if((bool) m.Invoke(reflectOb, args))
                            Console.WriteLine("14 is between x and y");
                        else
                            Console.WriteLine("14 is not between x and y");
                    }
                    break;

                case 2: // two args
                    if((pi[0].ParameterType == typeof(int)) &&
                       (pi[1].ParameterType == typeof(int)))
                    {
                        object[] args = new object[2];
                        args[0] = 9;
                        args[1] = 18;
                        m.Invoke(reflectOb, args);
                    }
                    else if((pi[0].ParameterType == typeof(double)) &&
                            (pi[1].ParameterType == typeof(double)))
                    {
                        object[] args = new object[2];
                        args[0] = 1.12;
                        args[1] = 23.4;
                        m.Invoke(reflectOb, args);
                    }
                    break;
            }

            Console.WriteLine();
        }
    }
}
