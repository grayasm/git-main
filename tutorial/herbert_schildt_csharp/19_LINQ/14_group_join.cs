/*
    Create a Group Join
    As mentioned earlier, you can use into with join to create a
    group join, which creates a sequence in which each entry in
    the result consists of an entry from the first sequence and
    a group of all matching elements from the second sequence.
    No example was presented then because often a group join makes
    use of an anonymous type. Now that anonymous types have been
    covered, an example of a simple group join can be given.
*/


// Demonstrate a simple group join.
using System;
using System.Linq;


// This class links the name of a transport, such as Train,
// with its general classification, such as land, sea, or air.
class Transport
{
    public string Name { get; set; }
    public string How { get; set; }
    public Transport(string n, string h)
    {
        Name = n;
        How = h;
    }
}


class GroupJoinDemo
{
    static void Main()
    {
        // An array of transport classifications.
        string[] travelTypes = {
                                 "Air",
                                 "Sea",
                                 "Land"
                               };


        // An array of transports.
        Transport[] transports =
                               {
                                 new Transport("Bicycle", "Land"),
                                 new Transport("Balloon", "Air"),
                                 new Transport("Boat", "Sea"),
                                 new Transport("Jet", "Air"),
                                 new Transport("Canoe", "Sea"),
                                 new Transport("Biplane", "Air"),
                                 new Transport("Car", "Land"),
                                 new Transport("Cargo Ship", "Sea"),
                                 new Transport("Train", "Land")
                               };


        // Create a query that uses a group join to produce
        // a list of item names and IDs organized by category.
        var byHow = from how in travelTypes
                    join trans in transports
                    on how equals trans.How
                    into lst
                    select new { How = how, Tlist = lst };



        // Execute the query and display the results.
        foreach(var t in byHow)
        {
            Console.WriteLine("{0} transportation includes:", t.How);
            foreach(var m in t.Tlist)
                Console.WriteLine(" " + m.Name);
            Console.WriteLine();
        }
    }
}
