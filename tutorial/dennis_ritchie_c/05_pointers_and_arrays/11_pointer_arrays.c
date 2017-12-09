/* Cap.5 Pointers and Arrays, pag.113

   Consider the problem of writing a function month_name(n), which returns
   a pointer to a character string containing the name of the n-th month.
   This is an ideal application for an internal static array.
*/


#include <stdio.h>

/* month_name: return name of n-th month */
char *month_name(int n)
{
    static char *name[] = {
        "Illegal month",
        "January", "February", "March",
        "April", "May", "June",
        "July", "August", "September",
        "October", "November", "December"
    };

    return (n > 0 && n < 13) ? name[n] : name[0];
}

main()
{
    printf("month_name(5) = %s\n", month_name(5));
}
