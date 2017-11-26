/* Cap.1 A Tutorial Introduction, pag.31

   Exercise 1-19  Write a function reverse that reverses the character string s.
                  Use it to write a program that reverses its input a line
                  at a time.
*/

#include <stdio.h>
#include <string.h>


void reverse(char* s, int l)
{
    if (s && *s != '\0')
    {
        char *e = s + l - 1;
        char t;

        while (s < e)
        {
            printf ("s=%c e=%c t=%c\n", *s, *e, t);
            t = *s;
            *s = *e;
            *e = t;
            s++;
            e--;
        }
    }
}

main()
{
    char s[] = "abcd0123";
    printf("%s %d\n", s, strlen(s));
    reverse(s, strlen(s));
    printf("%s %d\n", s, strlen(s));
}

/*
  abcd0123 8
  s=a e=3 t=
  s=b e=2 t=a
  s=c e=1 t=b
  s=d e=0 t=c
  3210dcba 8
*/
