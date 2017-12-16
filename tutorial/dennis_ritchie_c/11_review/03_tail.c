/* Mihai: implement the tail program from UNIX utils
 */

#include <stdio.h>
#include <stdlib.h>

#define MAXLINE 1000

main(int argc, char *argv[])
{
    int n;
    char line[MAXLINE];
    char **lines;

    if(argc < 2) {
        printf("use: program n < file.txt\n");
        return;
    }

    n = atoi(argv[1]);

    /* get line by line
       store each line into lines;??
       count lines;

       if EOF
       if n lines are available :
       print all lines
       else:
       print all available lines;
    */
}
