// Demonstrate the generic Dictionary<TKey, TValue> class.
using System;
using System.Collections.Generic;


class GenDictionaryDemo
{
    static void Main()
    {
        // Create a Dictionary that holds employee
        // names and their corresponding salary.
        Dictionary<string, double> dict = new Dictionary<string, double>();

        // Add elements to the collection.
        dict.Add("Butler, John", 73000);
        dict.Add("Swartz, Sarah", 59000);
        dict.Add("Pyke, Thomas", 45000);
        dict.Add("Frank, Ed", 99000);


        // Get a collection of the keys (names).
        ICollection<string> c = dict.Keys;

        // Use the keys to obtain the values (salaries).
        foreach(string str in c)
            Console.WriteLine("{0}, Salary: {1:C}", str, dict[str]);
    }
}
