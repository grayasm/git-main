using System;

class Arrays
{
    static void Main()
    {
        // Demonstrate a one-dimensional array.
        int[] sample = new int[10];

        int i;
        for(i = 0; i < 10; i = i+1)
            sample[i] = i;

        for(i = 0; i < 10; i = i+1)
            Console.WriteLine("sample[" + i + "]: " + sample[i]);


        // Compute the average of a set of values.
        int[] nums = new int[10];
        int avg = 0;
        nums[0] = 99;
        nums[1] = 10;
        nums[2] = 100;
        nums[3] = 18;
        nums[4] = 78;
        nums[5] = 23;
        nums[6] = 63;
        nums[7] = 9;
        nums[8] = 87;
        nums[9] = 49;

        for(i=0; i < 10; i++)
            avg = avg + nums[i];

        avg = avg / 10;

        Console.WriteLine("Average: " + avg);


        // Compute the average of a set of values.
        int[] nums2 = { 99, 10, 100, 18, 78, 23, 63, 9, 87, 49 };
        avg = 0;
        for(i=0; i < 10; i++)
            avg = avg + nums2[i];

        avg = avg / 10;

        Console.WriteLine("Average: " + avg);


        // Demonstrate an array overrun.
        int[] sample2 = new int[10];
        
        // Generate an array overrun.
        for(i = 0; i < 100; i = i+1)
            sample2[i] = i;
    }
}