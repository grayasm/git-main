/*
    System contains the following
    CLASSES:
    --------
    ActivationContext           Activator                 AppDomain
    AppDomainManager            AppDomainSetup            ApplicationId
    ApplicationIdentity         Array                     AssemblyLoadEventArgs
    Attribute                   AttributeUsageAttribute   BitConverter
    Buffer                      CharEnumerator            CLSCompliantAttribute
    Console                     ConsoleCancelEventArgs    ContextBoundObject
    ContextStaticAttribute      Convert                   DBNull
    Delegate                    Enum                      Environment
    EventArgs                   Exception                 FileStyleUriParser
    FlagsAttribute              FtpStyleUriParser         GC
    GenericUriParser            GopherStyleUriParser      HttpStyleUriParser
    Lazy<T>                     Lazy<T, TMetadata>        LdapStyleUriParser
    LoaderOptimizationAttribute LocalDataStoreSlot        MarshalByRefObject
    Math                        MTAThreadAttribute        MulticastDelegate
    NetPipeStyleUriParser       NetTcpStyleUriParser      NewsStyleUriParser
    NonSerializedAttribute      Nullable                  Object
    ObsoleteAttribute           OperatingSystem           ParamArrayAttribute
    Random                      ResolveEventArgs          SerializableAttribute
    STAThreadAttribute          String                    StringComparer
    ThreadStaticAttribute       TimeZone                  TimeZoneInfo
    TimeZoneInfo.AdjustmentRule Tuple                 Tuple<...> (various forms)
    Type                      UnhandledExceptionEventArgs Uri
    UriBuilder                  UriParser                 UriTemplate
 UriTemplateEquivalenceComparer UriTemplateMatch          UriTemplateTable
    UriTypeConverter            ValueType                 Version
    WeakReference

    STRUCTURES:
    -----------
    ArgIterator                 ArraySegment<T>           Boolean
    Byte                        Char                      ConsoleKeyInfo
    DateTime                    DateTimeOffset            Decimal
    Double                      Guid                      Int16
    Int32                       Int64                     IntPtr
    ModuleHandle                Nullable<T>               RuntimeArgumentHandle
    RuntimeFieldHandle          RuntimeMethodHandle       RuntimeTypeHandle
    Sbyte                       Single                    TimeSpan
    TimeZoneInfo.TransitionTime TypedReference            UInt16
    UInt32                      UInt64                    UIntPtr
    Void

    INTERFACES: ... pag.640
    DELEGATES:  ... pag.641
    ENUMERATIONS:.. pag.641
*/


// Using the System.Math class.

// Implement the Pythagorean Theorem.

using System;


class Pythagorean
{
    static void Main()
    {
        double s1;
        double s2;
        double hypot;
        string str;

        Console.WriteLine("Enter length of first side: ");
        str = Console.ReadLine();
        s1 = Double.Parse(str);

        Console.WriteLine("Enter length of second side: ");
        str = Console.ReadLine();
        s2 = Double.Parse(str);
        hypot = Math.Sqrt(s1*s1 + s2*s2);

        Console.WriteLine("Hypotenuse is " + hypot);
    }
}
