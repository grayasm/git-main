using System;

class Example
{
    static void Main()
    {
        int i;

        // Use goto with a switch.
        for(i=1; i < 5; i++)
        {
            switch(i)
            {
            case 1:
                Console.WriteLine("In case 1");
                goto case 3;

            case 2:
                Console.WriteLine("In case 2");
                goto case 1;

            case 3:
                Console.WriteLine("In case 3");
                goto default;

            default:
                Console.WriteLine("In default");
                break;
            }

            Console.WriteLine();
        }
        // goto case 1; // Error! Can't jump into a switch.


        // Demonstrate the goto.
        int j = 10, k = 10;

        for(i=0; i < 10; i++)
        {
            for(j=0; j < 10; j++ )
            {
                for(k=0; k < 10; k++)
                {
                    Console.WriteLine("i, j, k: " + i + " " + j + " " + k);
                    if(k == 3) goto stop;
                }
            }
        }
        stop:
            Console.WriteLine("Stopped! i, j, k: " + i + ", " + j + " " + k);

    }
}