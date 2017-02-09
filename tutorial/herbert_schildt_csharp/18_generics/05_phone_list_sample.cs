/*
    To better understand the value of base type constraints, let’s work
    through another, more practical example. Assume you want to create a
    mechanism that manages lists of telephone numbers. Furthermore, assume
    you want to use different lists for different groupings of numbers.
    Specifically, you want one list for friends, another for suppliers,
    and so on.
*/

using System;

class NotFoundException : Exception
{
    /* Implement all of the Exception constructors. Notice that
       the constructors simply execute the base class constructor.
       Because NotFoundException adds nothing to Exception,
       there is no need for any further actions.
    */

    public NotFoundException() : base() { }
    public NotFoundException(string message) : base(message) { }
    public NotFoundException(string message, Exception innerException) :
           base(message, innerException) { }

    protected NotFoundException(
              System.Runtime.Serialization.SerializationInfo info,
              System.Runtime.Serialization.StreamingContext context) :
              base(info, context) { }
}


// A base class that stores a name and phone number.
class PhoneNumber
{
    public PhoneNumber(string n, string num)
    {
        Name = n;
        Number = num;
    }

    // Auto-implemented properties that hold a name and phone number.
    public string Number { get; set; }
    public string Name { get; set; }
}

// A class of phone numbers for friends.
class Friend : PhoneNumber
{
    public Friend(string n, string num, bool wk) :
           base(n, num)
    {
        IsWorkNumber = wk;
    }

    public bool IsWorkNumber { get; private set; }
    // ...
}

// A class of phone numbers for suppliers.
class Supplier : PhoneNumber
{
    public Supplier(string n, string num) :
           base(n, num) { }

    // ...
}


// Notice that this class does not inherit PhoneNumber.
class EmailFriend
{
    // ...
}


// PhoneList can manage any type of phone list
// as long as it is derived from PhoneNumber.
class PhoneList<T> where T : PhoneNumber
{
    T[] phList;
    int end;
    public PhoneList()
    {
        phList = new T[10];
        end = 0;
    }

    // Add an entry to the list.
    public bool Add(T newEntry)
    {
        if(end == 10) return false;
        phList[end] = newEntry;
        end++;
        return true;
    }

    // Given a name, find and return the phone info.
    public T FindByName(string name)
    {
        for(int i=0; i<end; i++)
        {
            // Name can be used because it is a member of
            // PhoneNumber, which is the base class constraint.
            if(phList[i].Name == name)
                return phList[i];
        }

        // Name not in list.
        throw new NotFoundException();
    }

    // Given a number, find and return the phone info.
    public T FindByNumber(string number)
    {
        for(int i=0; i<end; i++)
        {
            // Number can be used because it is also a member of
            // PhoneNumber, which is the base class constraint.
            if(phList[i].Number == number)
                return phList[i];
        }

        // Number not in list.
        throw new NotFoundException();
    }
    // ...
}


// Demonstrate base class constraints.
class UseBaseClassConstraint
{
    static void Main()
    {
        // The following code is OK because Friend
        // inherits PhoneNumber.
        PhoneList<Friend> plist = new PhoneList<Friend>();
        plist.Add(new Friend("Tom", "555-1234", true));
        plist.Add(new Friend("Gary", "555-6756", true));
        plist.Add(new Friend("Matt", "555-9254", false));

        try
        {
            // Find the number of a friend given a name.
            Friend frnd = plist.FindByName("Gary");
            Console.Write(frnd.Name + ": " + frnd.Number);
            if(frnd.IsWorkNumber)
                Console.WriteLine(" (work)");
            else
                Console.WriteLine();
        }
        catch(NotFoundException)
        {
            Console.WriteLine("Not Found");
        }
        Console.WriteLine();

        // The following code is also OK because Supplier
        // inherits PhoneNumber.
        PhoneList<Supplier> plist2 = new PhoneList<Supplier>();
        plist2.Add(new Supplier("Global Hardware", "555-8834"));
        plist2.Add(new Supplier("Computer Warehouse", "555-9256"));
        plist2.Add(new Supplier("NetworkCity", "555-2564"));


        try
        {
            // Find the name of a supplier given a number.
            Supplier sp = plist2.FindByNumber("555-2564");
            Console.WriteLine(sp.Name + ": " + sp.Number);
        }
        catch(NotFoundException)
        {
            Console.WriteLine("Not Found");
        }

        // The following declaration is invalid because EmailFriend
        // does NOT inherit PhoneNumber.
        // PhoneList<EmailFriend> plist3 =
        // new PhoneList<EmailFriend>(); // Error!
    }
}
