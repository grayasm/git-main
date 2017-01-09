using System;



class Rect
{
    public int Width;
    public int Height;

    public Rect(int w, int h)
    {
        this.Width = w;     // using "this."
        Height = h;         // possible without "this."
    }

    public int Area()
    {
        return this.Width * this.Height;  // here using "this."
    }
}


class ThisKeyword
{
    static void Main()
    {
        Rect r1 = new Rect(4, 5);
        Rect r2 = new Rect(7, 9);

        Console.WriteLine("Area of r1: " + r1.Area());
        Console.WriteLine("Area of r2: " + r2.Area());

    }
}