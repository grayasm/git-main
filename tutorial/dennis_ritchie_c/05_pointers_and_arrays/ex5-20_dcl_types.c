/* Cap.5 Pointers and Arrays, pag.126

   Exercise 5-20: Expand dcl to handle declarations with function argument
                  types, qualifiers like const, and so on.
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
void dclspec(void);
int typespec(void);
int typequal(void);
int compare(char **, char **);
int gettoken(void);
int nexttoken(void);


int tokentype;
char token[MAXTOKEN];       /* last token string */
char name[MAXTOKEN];        /* identifier name */
char datatype[MAXTOKEN];    /* data type = char, int, etc. */
char out[1000];             /* output string */
int prevtoken = NO;


int main(void)
{
    int type;
    char temp[MAXTOKEN];

    while (gettoken() != EOF)
    {
        strcpy(out, token);

        while ((type = gettoken()) != '\n')
            if (type == PARENS || type == BRACKETS)
                strcat(out, token);
            else if (type == '*')
            {
                if ((type = nexttoken()) == PARENS || type == BRACKETS)
                    sprintf(temp, "(*%s)", out);
                else
                    sprintf(temp, "*%s", out);
                strcpy(out, temp);
            }
            else if (type == NAME)
            {
                sprintf(temp, " %s %s", token, out);
                strcpy(out, temp);
            }
            else
                printf("invalid input at %s \n", token);
        printf("%s\n", out);
    }
    return 0;
}


/* dcl: parse a declarator */

void dcl(void)
{
    int ns;

    for (ns = 0; gettoken() == '*'; ns++) /* count *'s */
        ;
    dirdcl();
    while (ns-- > 0)
        strcat(out, "pointer to");
}

/* dirdcl: parse a direct declaration */
void dirdcl(void)
{
    int type;
    void parmdcl(void);

    if (tokentype == '(')    /* (dcl)    */
    {
        dcl();
        if (tokentype != ')')
            errmsg("error: missing ) \n");
    }
    else if (tokentype == NAME)
    {
        if (name[0] == '\0')
            strcpy(name, token);
    }
    else
        prevtoken = YES;

    while ((type = gettoken()) == PARENS || type == BRACKETS || type == '(')
        if (type == PARENS)
            strcat(out, "function returning");
        else if (type == '(')
        {
            strcat(out, "function expecting");
            parmdcl();
            strcat(out, "and returning");
        }
        else
        {
            strcat(out, "array");
            strcat(out, token);
            strcat(out, "of");
        }
}

/* errmsg: print error message and indicate avail. token */
void errmsg(char *msg)
{
    printf("%s", msg);
    prevtoken = YES;
}


/* The source file parmdcl.c */

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>


/* parmdcl: parse a parameter declarator */

void parmdcl(void)
{
    do
    {
        dclspec();
    } while (tokentype == ',');

    if (tokentype != ')')
        errmsg("missing ) in parameter declaration \n");
}


/* dclspec: declaration specification */

void dclspec(void)
{
    char temp[MAXTOKEN];

    temp[0] = '\0';
    gettoken();

    do
    {
        if (tokentype != NAME)
        {
            prevtoken = YES;
            dcl();
        }
        else if (typespec() == YES)
        {
            strcat(temp, " ");
            strcat(temp, token);
            gettoken();
        }
        else if (typequal() == YES)
        {
            strcat(temp, " ");
            strcat(temp, token);
            gettoken();
        }
        else
            errmsg("unknown type in parameter list \n");
    } while (tokentype != ',' && tokentype != ')');

    strcat(out, temp);
    if (tokentype == ',')
        strcat(out, ",");
}



/* typespec: return YES if token is a type-specifier    */
int typespec(void)
{
    static char *types[] =
    {
        "char",
        "int",
        "void"
    };

    char *pt = token;

    if (bsearch(&pt, types, sizeof(types) / sizeof(char *), sizeof(char *), compare) == NULL)
        return NO;
    else
        return YES;
}

/* typequal: return YES if token is a type-qualifier */
int typequal(void)
{
    static char *typeq[] =
    {
        "const",
        "volatile"
    };

    char *pt = token;

    if (bsearch(&pt, typeq, sizeof(typeq) / sizeof(char *), sizeof(char *), compare) == NULL)
        return NO;
    else
        return YES;
}

/* compare: compare two strings for bsearch */

int compare(char **s, char **t)
{
    return strcmp(*s, *t);
}


/* nexttoken: get the next token and push it back */
int nexttoken(void)
{
    int type;
    extern int prevtoken;

    type = gettoken();
    prevtoken = YES;
    return type;
}

#include<ctype.h>
#include<string.h>


int gettoken(void)  /* return next token */
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
        for (*p++ = c; isalnum(c = getch());)
            *p++ = c;
        *p = '\0';
        ungetch(c);
        return tokentype = NAME;
    }
    else
        return tokentype = c;
}

#define BUFSIZE 100
char buf[BUFSIZE];  /* buffer for ungetch */
int bufp = 0;

int getch(void)     /* get a(possibly pushed back) character */
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
