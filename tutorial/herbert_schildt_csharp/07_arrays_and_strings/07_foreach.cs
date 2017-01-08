using System;



class ForeachDemo
{
    static void Main()
    {
        // Use the foreach loop.
        int sum = 0;
        int[] nums0 = new int[10];

        // Give nums some values.
        for(int i = 0; i < 10; i++)
            nums0[i] = i;

        // Use foreach to display and sum the values.
        foreach(int x in nums0)
        {
            Console.WriteLine("Value is: " + x);
            sum += x;
        }

        Console.WriteLine("Summation: " + sum);


        // Use break with a foreach.
        sum = 0;
        int[] nums = new int[10];

        // Give nums some values.
        for(int i = 0; i < 10; i++)
            nums[i] = i;

        // Use foreach to display and sum the values.
        foreach(int x in nums)
        {
            Console.WriteLine("Value is: " + x);
            sum += x;
            if(x == 4) break; // stop the loop when 4 is obtained
        }

        Console.WriteLine("Summation of first 5 elements: " + sum);


        // Use foreach on a two-dimensional array.
        sum = 0;
        int[,] nums2 = new int[3,5];


        // Give nums some values.
        for(int i = 0; i < 3; i++)
            for(int j=0; j < 5; j++)
                nums2[i,j] = (i+1)*(j+1);

        // Use foreach to display and sum the values.

        foreach(int x in nums2)
        {
            Console.WriteLine("Value is: " + x);

            sum += x;
        }

        Console.WriteLine("Summation: " + sum);


        // Search an array using foreach.

        int[] nums3 = new int[10];
        int val;
        bool found = false;

        // Give nums some values.
        for(int i = 0; i < 10; i++)
            nums3[i] = i;

        val = 5;

        // Use foreach to search nums for key.
        foreach(int x in nums3)
        {
            if(x == val)
            {
                found = true;
                break;
            }
        }


        if(found)
            Console.WriteLine("Value found!");

    }
}