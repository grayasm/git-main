/* Cap.5 Pointers and Arrays, pag.117

   This program searches for a patter in the input.
   Use options: -x to print line that do not match the pattern, otherwise
                   will print lines that do match with the pattern
                -n will print also the line number
   program -x -n pattern < file
*/

#include <stdio.h>
#include <string.h>
#define MAXLINE 1000


int getline_(char *line, int max);

/* find: print lines that match pattern from 1st arg */
int main(int argc, char *argv[])
{
    char line[MAXLINE];
    long lineno = 0;
    int c, except = 0, number = 0, found = 0;

    while (--argc > 0 && (*++argv)[0] == '-')
        while (c = *++argv[0])
            switch(c)
            {
            case 'x':
                except = 1;
                break;
            case 'n':
                number = 1;
                break;
            default:
                printf("find: illegal option %c\n", c);
                argc = 0;
                found = -1;
                break;
            }

    if (argc != 1)
        printf("Usage: find -x -n pattern\n");
    else
        while(getline_(line, MAXLINE) > 0) {
            lineno++;
            if ((strstr(line, *argv) != NULL) != except) {
                if (number)
                    printf("%ld:", lineno);
                printf("%s", line);
                found++;
            }
        }
    return found;
}


int getline_(char *s, int lim)
{
    int c, i;

    for (i=0; i<lim-1 && (c = getchar())!= EOF && c!='\n'; ++i)
        s[i] = c;
    if (c == '\n') {
        s[i] = c;
        ++i;
    }
    s[i] = '\0';
    return i;
}
