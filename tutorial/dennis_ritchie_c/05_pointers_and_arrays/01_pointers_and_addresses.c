/* Cap.5 Pointers and Arrays, pag.94

   Pointers and Addresses
   The unary & operator gives the address of an object (variable).
   The unary * operator is the indirection or dereferencing operator; when
   applied to a pointer it accesses the object the pointer points to.
*/

#include <stdio.h>


main()
{
    int x = 1, y = 2, z[10];
    int *ip;          /* ip is a pointer to int */

    ip = &x;          /* ip now points to x */
    y = *ip;          /* y is now 1 */
    *ip = 0;          /* x is now 0 */
    ip = &z[0];       /* ip points to z[0] */
}
