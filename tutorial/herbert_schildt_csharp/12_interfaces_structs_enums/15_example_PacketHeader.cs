// Structures are good when grouping small amounts of data.

using System;


// Define a packet structure.
struct PacketHeader
{
    public uint PackNum;    // packet number
    public ushort PackLen;  // length of packet
}


// Use PacketHeader to create an e-commerce transaction record.
class Transaction
{
    static uint transacNum = 0;
    PacketHeader ph; // incorporate PacketHeader into Transaction
    string accountNum;
    double amount;

    public Transaction(string acc, double val)
    {
        // create packet header
        ph.PackNum = transacNum++;
        ph.PackLen = 512; // arbitrary length
        accountNum = acc;
        amount = val;
    }

    // Simulate a transaction.
    public void sendTransaction()
    {
        Console.WriteLine("Packet #: " + ph.PackNum +
                          ", Length: " + ph.PackLen +
                          ",\n Account #: " + accountNum +
                          ", Amount: {0:C}\n", amount);
    }
}


// Demonstrate Packet.
class PacketDemo
{
    static void Main()
    {
        Transaction t = new Transaction("31243", -100.12);
        Transaction t2 = new Transaction("AB4655", 345.25);
        Transaction t3 = new Transaction("8475-09", 9800.00);

        t.sendTransaction();
        t2.sendTransaction();
        t3.sendTransaction();
    }
}
