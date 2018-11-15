/* Cap.5 Pointers and Arrays, pag.126

   Exercise 5-18: Make dcl recover from input errors.
*/

#include<stdio.h>
#include<string.h>
#include<ctype.h>

#define MAXTOKEN 100
enum { NAME, PARENS, BRACKETS };
enum { NO, YES };

void dcl(void);
void dirdcl(void);
void errmsg(char *);

int gettoken(void);
int tokentype;              /* type of last token */
char token[MAXTOKEN];       /* last token string */
char name[MAXTOKEN];        /* identifier name */
char datatype[MAXTOKEN];    /* data type = char, int, etc. */
char out[1000];             /* output string */
int prevtoken = NO;


int main()
{
    while (gettoken() != EOF) {     /* 1st token on line */
        strcpy(datatype, token);    /* is the datatype */
        out[0] = '\0';
        dcl();  /* parse rest of line */
        if (tokentype != '\n')
            printf("syntax error\n");
        printf("%s: %s %s\n", name, out, datatype);
    }
    return 0;
}


/* dcl: parse a declarator  */
void dcl(void)
{
    int ns;

    for (ns = 0; gettoken() == '*';)     /* count *'s    */
        ns++;

    dirdcl();

    while (ns-- > 0)
        strcat(out, "pointer to");
}


/* dirdcl: parse a direct declaration */
void dirdcl(void)
{
    int type;

    if (tokentype == '(')
    {
        dcl();

        if (tokentype != ')')
            errmsg("error: missing ) \n");
    }
    else if (tokentype == NAME)
        strcpy(name, token);
    else
        errmsg("error: expected name or (dcl) \n");

    while ((type = gettoken()) == PARENS || type == BRACKETS)
        if (type == PARENS)
            strcat(out, "function returning");
        else
        {
            strcat(out, "array");
            strcat(out, token);
            strcat(out, "of");
        }
}

/* errmsg:  print error message and indicate avail. token */

void errmsg(char *msg)
{
    printf("%s", msg);
    prevtoken = YES;
}

/* The Source file gettoken.c */

#include<ctype.h>
#include<string.h>


/* gettoken : return next token */

int gettoken(void)
{
    int c, getch(void);
    void ungetch(int);

    char *p = token;

    if (prevtoken == YES)
    {
        prevtoken = NO;

        return tokentype;
    }

    while ((c = getch()) == ' ' || c == '\t')
        ;

    if (c == '(')
    {
        if ((c = getch()) == ')')
        {
            strcpy(token, "()");
            return tokentype = PARENS;
        }
        else
        {
            ungetch(c);
            return tokentype = '(';
        }
    }
    else if (c == '[')
    {
        for (*p++ = c; (*p++ = getch()) != ']';)
            ;
        *p = '\0';

        return tokentype = BRACKETS;
    }
    else if (isalpha(c))
    {
        for (*p++ = c; isalnum(c = getch()); )
            *p++ = c;

        *p = '\0';

        ungetch(c);
        return tokentype = NAME;
    }
    else
        return tokentype = c;
}

#define BUFSIZE 100

char buf[BUFSIZE];      /* buffer for ungetch   */
int bufp = 0;           /* next free position in buf    */

int getch(void)         /* get a (possibly pushed back) character */
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c)
{
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters \n");
    else
        buf[bufp++] = c;
}
