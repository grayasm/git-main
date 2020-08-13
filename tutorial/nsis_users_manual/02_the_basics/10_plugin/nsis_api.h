/******************************************************************************
    NSIS API
    This file shows how to extract the parameters passed to a plug-in's method.
    It uses stack_t* pointer to linked list to iterate and get each param.
    Source: https://nsis-dev.github.io/NSIS-Forums/html/t-291309.html
******************************************************************************/

#ifndef __nsis_api_h__
#define __nsis_api_h__


/******************************************************************************
/* Defines                                                                    *
******************************************************************************/
// for NSIS stack
#define EXDLL_INIT()                \
{                                   \
    g_stacktop      = stacktop;     \
    g_variables     = variables;    \
    g_stringsize    = string_size;  \
}
#define MAX_STRLEN      1024


/******************************************************************************
/* NSIS stack structure                                                       *
******************************************************************************/
typedef struct _stack_t 
{
    struct  _stack_t* next;
    char              text[MAX_STRLEN];
} stack_t;


/******************************************************************************
/* Global values                                                              *
******************************************************************************/
// for NSIS stack
stack_t**       g_stacktop;
char*           g_variables;
unsigned int    g_stringsize;


/******************************************************************************
* FUNCTION NAME: pushstring                                                   *
* PARAMETER: STR                                                              *
* PURPOSE: Removes the element from the top of the NSIS stack and puts        *
*          it in the buffer.                                                  *
* RETURN: TRUE if stack is empty, FALSE if value is loaded.                   *
******************************************************************************/
int popstring(char* str)
{
    stack_t* th;

    if (!g_stacktop || !*g_stacktop)
        return 1;

    th = (*g_stacktop);
    lstrcpy(str, th->text);
    *g_stacktop = th->next;

    GlobalFree((HGLOBAL)th);

    return 0;
}

/******************************************************************************
* FUNCTION NAME: pushstring                                                   *
* PARAMETER: STR                                                              *
* PURPOSE: Adds an element to the top of the NSIS stack                       *
******************************************************************************/
void pushstring(const char* str)
{
    stack_t* th;

    if (!g_stacktop)
        return;

    th = (stack_t*)GlobalAlloc(GPTR, sizeof(stack_t) + g_stringsize);
    lstrcpyn(th->text, str, g_stringsize);
    th->next = *g_stacktop;

    *g_stacktop = th;
}


#endif // __nsis_api_h__
