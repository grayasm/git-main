// Use IComparer<T>.
using System;
using System.Collections.Generic;
// Create an IComparer<T> for Inventory objects.
class CompInv<T> : IComparer<T> where T : Inventory {
 // Implement the IComparer<T> interface.
 public int Compare(T x, T y) {
  return string.Compare(x.name, y.name, StringComparison.Ordinal);
 }
}
class Inventory {
 public string name;
 double cost;
 int onhand;
 public Inventory(string n, double c, int h) {
 name = n;
 cost = c;
 onhand = h;
 }
 public override string ToString() {
 return
 String.Format("{0,-10}Cost: {1,6:C} On hand: {2}",
 name, cost, onhand);
 }
}
class GenericIComparerDemo {
 static void Main() {
 CompInv<Inventory> comp = new CompInv<Inventory>();
 List<Inventory> inv = new List<Inventory>();
 // Add elements to the list.
 inv.Add(new Inventory("Pliers", 5.95, 3));
 inv.Add(new Inventory("Wrenches", 8.29, 2));
 inv.Add(new Inventory("Hammers", 3.50, 4));
 inv.Add(new Inventory("Drills", 19.88, 8));
 Console.WriteLine("Inventory list before sorting:");
 foreach(Inventory i in inv) {
 Console.WriteLine(" " + i);
 }
 Console.WriteLine();
 // Sort the list using an IComparer.
 inv.Sort(comp);
 Console.WriteLine("Inventory list after sorting:");
 foreach(Inventory i in inv) {
 Console.WriteLine(" " + i);
 }
 }
}
