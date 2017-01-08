using System;

class Example
{
    static void Main()
    {

        // Demonstrate the switch.
        int i;

        for(i=0; i<10; i++)
            switch(i)
            {
            case 0:
                Console.WriteLine("i is zero");
                break;
            case 1:
                Console.WriteLine("i is one");
                break;
            case 2:
                Console.WriteLine("i is two");
                break;
            case 3:
                Console.WriteLine("i is three");
                break;
            case 4:
                Console.WriteLine("i is four");
                break;
            default:
                Console.WriteLine("i is five or more");
                break;
            }


        // Use a char to control the switch.
        char ch;

        for(ch='A'; ch<= 'E'; ch++)
            switch(ch)
            {
            case 'A':
                Console.WriteLine("ch is A");
                break;

            case 'B':
                Console.WriteLine("ch is B");
                break;

            case 'C':
                Console.WriteLine("ch is C");
                break;

            case 'D':
                 Console.WriteLine("ch is D");
                 break;

            case 'E':
                Console.WriteLine("ch is E");
                break;
            }

        // Empty cases can fall through.
        for(i=1; i < 5; i++)
            switch(i)
            {
            case 1:
            case 2:
            case 3:
                Console.WriteLine("i is 1, 2 or 3");
                break;
            case 4:
                Console.WriteLine("i is 4");
                break;
            }

        //Nested switch Statements
        char ch1 = 'A';
        char ch2 = 'A';

        switch(ch1)
        {
        case 'A':
            Console.WriteLine("This A is part of outer switch.");

            switch(ch2)
            {
            case 'A':
                Console.WriteLine("This A is part of inner switch");
                break;

            case 'B':
                Console.WriteLine("This A is part of inner switch");
                break;

            default:
                Console.WriteLine("This default is part of inner switch");
                break;
            } // end of inner switch
            break;

        case 'B':
             Console.WriteLine("This B is part of outer switch");
             break;

        default:
             break;
        }

    }
}