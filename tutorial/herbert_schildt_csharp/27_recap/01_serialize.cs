// https://www.c-sharpcorner.com/article/serializing-objects-in-C-Sharp/

using System;
using System.IO;
using System.Runtime.Serialization;
using System.Runtime.Serialization.Formatters.Binary;


public class SerialTest
{
    public void SerializeNow()
    {
        ClassToSerialize c = new ClassToSerialize();
        File f = new File("temp.dat");
        Stream s = f.Open(FileMode.Create);
        BinaryFormatter b = new BinaryFormatter();
        b.Serialize(s, c);
        s.Close();
    }

    public void DeSerializeNow()
    {
        ClassToSerialize c = new ClassToSerialize();
        File f = new File("temp.dat");
        Stream s = f.Open(FileMode.Open);
        BinaryFormatter b = new BinaryFormatter();
        c = (ClassToSerialize) b.Deserialize(s);
        Console.WriteLine(c.name);
        s.Close();
    }

    public static void Main(string[] s)
    {
        SerialTest st = new SerialTest();
        st.SerializeNow();
        st.DeSerializeNow();
    }
}


public class ClassToSerialize
{
    public int age = 100;
    public string name = "bipin";
}