/* An array name without an index yields a pointer to the start of the array.
*/

using System;


class PtrArray
{
    unsafe static void Main()
    {
        int[] nums = new int[10];

        fixed(int* p = &nums[0], p2 = nums)
        {
            if(p == p2)
                Console.WriteLine("p and p2 point to same address.");
        }
    }
}
