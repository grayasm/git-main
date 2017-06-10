/*
    Three Built-in Attributes
    C# defines many built-in attributes, but three are especially
    important because they apply to a wide variety of situations:
    AttributeUsage, Conditional, and Obsolete.
*/

// Use a property as a named attribute parameter.

using System;
using System.Reflection;

[AttributeUsage(AttributeTargets.All)]
public class RemarkAttribute : Attribute
{
    string pri_remark; // underlies Remark property
    public string Supplement; // this is a named parameter

    public RemarkAttribute(string comment)
    {
        pri_remark = comment;
        Supplement = "None";
        Priority = 1;
    }

    public string Remark
    {
        get {
            return pri_remark;
        }
    }

    // Use a property as a named parameter.
    public int Priority { get; set; }
}


[RemarkAttribute("This class uses an attribute.",
 Supplement = "This is additional info.",
 Priority = 10)]
class UseAttrib
{
    // ...
}


class NamedParamDemo
{
    static void Main()
    {
        Type t = typeof(UseAttrib);
        Console.Write("Attributes in " + t.Name + ": ");
        object[] attribs = t.GetCustomAttributes(false);

        foreach(object o in attribs)
        {
            Console.WriteLine(o);
        }

        // Retrieve the RemarkAttribute.
        Type tRemAtt = typeof(RemarkAttribute);
        RemarkAttribute ra = (RemarkAttribute)
        Attribute.GetCustomAttribute(t, tRemAtt);
        Console.Write("Remark: ");
        Console.WriteLine(ra.Remark);
        Console.Write("Supplement: ");
        Console.WriteLine(ra.Supplement);
        Console.WriteLine("Priority: " + ra.Priority);
    }
}
