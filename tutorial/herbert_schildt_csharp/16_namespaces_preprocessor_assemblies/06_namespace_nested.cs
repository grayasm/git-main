// Namespaces can be nested.

using System;


namespace NS1
{
    class ClassA
    {
        public ClassA()
        {
            Console.WriteLine("constructing ClassA");
        }
    }

    namespace NS2  // a nested namespace
    {
        class ClassB
        {
            public ClassB()
            {
                Console.WriteLine("constructing ClassB");
            }
        }
    }
}


class NestedNSDemo
{
    static void Main()
    {
        NS1.ClassA a = new NS1.ClassA();

        // NS2.ClassB b = new NS2.ClassB(); // Error!!! NS2 is not in view

        NS1.NS2.ClassB b = new NS1.NS2.ClassB(); // this is right
    }
}
