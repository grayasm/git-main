/* Synchronization construct: atomic

   syntax: #pragma omp atomic
               statement

   The atomic construct, which also enables multiple threads to update shared
   data without interference, can be an efficient alternative to the critical
   region. In contrast to other constructs, it is applied only to the (single)
   assignment statement that immediately follows it;
 */



#include <stdio.h>
#include <omp.h>


int main(int argc, char** argv)
{
    const int MAX=5;
    int i, a[MAX], sum;
    for (i=0; i<MAX; i++) a[i] = i;

#pragma omp parallel for shared(sum) private(i)
    for (i=0; i<MAX; i++)
    {

#pragma omp critical (update_sum)
        sum += a[i];

    }

    printf ("sum= %d\n", sum); // sum(0:4)=4*5/2 = 20/2 = 10;
    if (sum == 10)

        return 0;
}
