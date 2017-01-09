using System;


class LengthDemo
{
    static void Main()
    {

        // Use the Length array property.
        int i,j;
        int[] nums0 = new int[10];

        Console.WriteLine("Length of nums is " + nums0.Length);

        // Use Length to initialize nums.
        for(i=0; i < nums0.Length; i++)
            nums0[i] = i * i;

        // Now use Length to display nums.
        Console.Write("Here is nums: ");
        for(i=0; i < nums0.Length; i++)
            Console.Write(nums0[i] + " ");

        Console.WriteLine();


        // Use the Length array property on a 3D array.
        int[,,] nums = new int[10, 5, 6];

        Console.WriteLine("Length of nums is " + nums.Length);


        // Reverse an array.

        int[] nums1 = new int[10];
        int[] nums2 = new int[10];

        for(i=0; i < nums1.Length; i++) nums1[i] = i;

        Console.Write("Original contents: ");

        for(i=0; i < nums2.Length; i++)
            Console.Write(nums1[i] + " ");

        Console.WriteLine();


        // Reverse copy nums1 to nums2.
        if(nums2.Length >= nums1.Length) // make sure nums2 is long enough
            for(i=0, j=nums1.Length-1; i < nums1.Length; i++, j--)
                nums2[j] = nums1[i];

        Console.Write("Reversed contents: ");

        for(i=0; i < nums2.Length; i++)
            Console.Write(nums2[i] + " ");

        Console.WriteLine();


        // Demonstrate Length with jagged arrays.
        int[][] network_nodes = new int[4][];
        network_nodes[0] = new int[3];
        network_nodes[1] = new int[7];
        network_nodes[2] = new int[2];
        network_nodes[3] = new int[5];

        // Fabricate some fake CPU usage data.
        for(i=0; i < network_nodes.Length; i++)
            for(j=0; j < network_nodes[i].Length; j++)
                network_nodes[i][j] = i * j + 70;

        Console.WriteLine("Total number of network nodes: " +
                          network_nodes.Length + "\n");

        for(i=0; i < network_nodes.Length; i++)
        {
            for(j=0; j < network_nodes[i].Length; j++)
            {
                Console.Write("CPU usage at node " + i + " CPU " + j + ": ");

                Console.Write(network_nodes[i][j] + "% ");

                Console.WriteLine();
            }

            Console.WriteLine();
        }

    }
}