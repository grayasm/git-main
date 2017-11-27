/* Cap.3 Control Flow, pag.64

   The following function itoa converts a number to a character string
   (the inverse of atoi). The job is slightly more complicated than might be
   though at first, because the easy methods of generating the digits generate
   them in the wrong order. We have chose to generate the string backwards,
   then reverse it.
*/

#include <stdio.h>

/* itoa: convert n to characters in s */
void itoa (int n, char s[])
{
	int i, sign;
	
	if ((sign = n) < 0)		/* record sign */
		n = -n;
	i = 0;
	do {		/* generate digits in reverse order */
		s[i++] = n % 10 + '0';		/* get next digit */
	} while ((n /= 10) > 0);		/* delete it */
	
	if (sign < 0)
		s[i++] = '-';
	s[i] = '\0';
	// reverse (s);
}

main()
{
	int n = -12345;
	char s[10];
	itoa(n, s);
	printf("itoa(%d)=%s\n", n, s);
}

/*
itoa(-12345)=54321-
*/