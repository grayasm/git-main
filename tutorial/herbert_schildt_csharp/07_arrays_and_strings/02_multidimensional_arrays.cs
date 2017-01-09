using System;


class MultiD
{
    static void Main()
    {
        int t, i;
        int[,] table = new int[3, 4];

        for(t=0; t < 3; ++t)
        {
            for(i=0; i < 4; ++i)
            {
                table[t, i] = (t*4) + i + 1;      // access with [index, index]
                Console.Write(table[t,i] + " ");
            }

            Console.WriteLine();
        }


        // Sum the values on a diagonal of a 3x3x3 matrix.
        int[,,] m = new int[3, 3, 3];
        int sum = 0;
        int n = 1;

        for(int x=0; x < 3; x++)
            for(int y=0; y < 3; y++)
                for(int z=0; z < 3; z++)
                    m[x, y, z] = n++;      // access with [index, index, index]

        sum = m[0, 0, 0] + m[1, 1, 1] + m[2, 2, 2];

        Console.WriteLine("Sum of first diagonal: " + sum);


        // Initialize a two-dimensional array.
        int[,] sqrs = {
                       { 1, 1 },
                       { 2, 4 },
                       { 3, 9 },
                       { 4, 16 },
                       { 5, 25 },
                       { 6, 36 },
                       { 7, 49 },
                       { 8, 64 },
                       { 9, 81 },
                       { 10, 100 }
                      };

        int j;
        for(i=0; i < 10; i++)
        {
            for(j=0; j < 2; j++)
                Console.Write(sqrs[i,j] + " ");

            Console.WriteLine();
        }
    }
}