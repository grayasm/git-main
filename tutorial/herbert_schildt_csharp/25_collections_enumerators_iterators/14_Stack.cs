// Demonstrate the Stack<T> class.
using System;
using System.Collections.Generic;


class GenStackDemo
{
    static void Main()
    {
        Stack<string> st = new Stack<string>();
        st.Push("One");
        st.Push("Two");
        st.Push("Three");
        st.Push("Four");
        st.Push("Five");

        while(st.Count > 0)
        {
            string str = st.Pop();
            Console.Write(str + " ");
        }

        Console.WriteLine();
    }
}
