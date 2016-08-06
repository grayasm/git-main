/*  The reduction clause is for specifying some forms of recurrence
    calculations (involving mathematically associative and commutative
    operators) so that they can be performed in parallel without code
    modification.

    The results will be shared and it is not necessary to specify the
    corresponding variables explicitly as “shared.”

    syntax: reduction(operator :list )

    Supported operators and initialization values:
    +  *  -   &   |  ^  &&   ||  (and similar ++ -- += -= *= etc)
    0  1  0  ~0   0  0   1    0

    Some restrictions are applied:
    ------------------------------
    -> Aggregate types (including arrays), pointer types, and reference types
    are not supported.
    -> A reduction variable must not be const-qualified.
    -> The operator specified on the clause can not be overloaded with respect
    to the variables that appear in the clause.
*/

#include <stdio.h>
#include <omp.h>


int main(int argc, char** argv)
{
    int i, sum=0, n=5;

#pragma omp parallel for shared(n) private(i) reduction(+:sum)
    for (i=0; i<n; i++)
    {
        sum += i;

    }/* end of parallel region */

    if (sum == 4*5/2) printf("sum=%d OK\n", sum);
    else              printf("sum=%d Error\n", sum);

    return 0;
}
