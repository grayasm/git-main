/* Space Complexity

   We do not care only about time, but also memory or space required by an algo.
   Space complexity is parallel concept to time complexity. If we need to create
   an array of size n, this will require O(n) space. If we need a two-dimensional
   array of size n x n, this will require O(n^2) space.

   Stack space in recursive calls counts too. For example, code like this
   would take O(n) time and O(n) space.
*/

int sum(int) {
    if (n <=0) {
        return 0;
    }
    return n + sum(n - 1);
}

/* Each call adds a level to the stack
   sum(4)
     -> sum(3)
       -> sum(2)
         -> sum(1)
           -> sum(0);
*/

/* The folling code will take O(n) calls to pairSum, that will exist
   simultaneously, and only O(1) space.
*/
int pairSumSequence(int n) {
    int sum = 0;
    for (int i = 0; i < n; i++) {
        sum += pairSum(i, i+1);
    }
    return sum;
}

int pairSum(int a, int b) {
    return a + b;
}
