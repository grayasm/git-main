// Return an object.

using System;


class Rect
{
    int width;
    int height;
    public Rect(int w, int h)
    {
        width = w;
        height = h;
    }

    public int Area()
    {
        return width * height;
    }

    public void Show()
    {
        Console.WriteLine(width + " " + height);
    }

    /* Return a rectangle that is a specified
       factor larger than the invoking rectangle. */
    public Rect Enlarge(int factor)
    {
        return new Rect(width * factor, height * factor);
    }
}


class RetObj
{
    static void Main()
    {
        Rect r1 = new Rect(4, 5);
        Console.Write("Dimensions of r1: ");
        r1.Show();
        Console.WriteLine("Area of r1: " + r1.Area());
        Console.WriteLine();

        // Create a rectangle that is twice as big as r1.
        Rect r2 = r1.Enlarge(2);

        Console.Write("Dimensions of r2: ");
        r2.Show();
        Console.WriteLine("Area of r2: " + r2.Area());
    }
}
