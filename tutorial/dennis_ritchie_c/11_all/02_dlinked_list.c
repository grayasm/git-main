/* Mihai: Implement a double-linked list in C.
 */

#include <stdio.h>
#include <stdlib.h>

struct node {
    struct node *next;
    struct node *prev;
    int v;
};

struct list {
    struct node *head;
    struct node *tail;
};

void list_init(struct list **l)
{
    if (*l != NULL)
        return;
    *l = (struct list*) malloc (sizeof(struct list*));
    (*l)->head = (*l)->tail = NULL;
}

void list_clean(struct list *l)
{
    struct node *n = l->head, *m;
    while (n)
    {
        m = n->next;
        free(n);
        n = m;
    }
    l->head = l->tail = NULL;
}

void list_add(struct list *l, int v)
{
    struct node *n;

    if (l->head == NULL) /* size:0 */
    {
        l->head = (struct node*) malloc(sizeof(struct node));
        l->head->prev = NULL;
        l->head->next = l->tail;
        l->head->v = v;
    }
    else if(l->tail == NULL) /* size:1 */
    {
        l->tail = (struct node*) malloc(sizeof(struct node));
        l->tail->prev = l->head;
        l->head->next = l->tail;
        l->tail->next = NULL;
        l->tail->v = v;
    }
    else /* size:>1 */
    {
        l->tail->next = (struct node*) malloc(sizeof(struct node));
        n = l->tail->next;
        n->next = NULL;
        n->prev = l->tail;
        n->v = v;
        l->tail = n;
    }
}

void list_print(struct list *l)
{
    struct node *n = l->head;

    printf("print list\n");
    while (n)
    {
        printf("%d\n", n->v);
        n = n->next;
    }
}

void list_rem(struct list *l, int v)
{
    struct node *f = l->head, *n, *p;
    while (f) {
        if (f->v == v) {
            /* is f is l->head:
               with l:size:1
               with l:size:>1 */
            if(f == l->head)
            {
                n = f->next;
                p = NULL;
                free(l->head);

                if (n) {
                    n->prev = NULL;
                    l->head = n;
                } else {
                    l->head = NULL;
                    l->tail = NULL;
                }
            }

            /* is f l->tail
               with size:1
               with size:>1 */
            else if(f == l->tail)
            {
                n = NULL;
                p = l->tail->prev;
                free(l->tail);

                if(p) {
                    p->next = NULL;
                    l->tail = p;
                } else {
                    l->head = NULL;
                    l->tail = NULL;
                }
            }
            else
            {
                p = f->prev;
                n = f->next;

                p->next = n;
                n->prev = p;

                free (f);
            }
            return;
        }
        f = f->next;
    }
}


main()
{
    struct list *l = NULL;
    list_init(&l);

    list_add(l, 10);
    list_add(l, 50);
    list_add(l, 51);
    list_add(l, 1);

    list_print(l);

    list_rem(l, 51);
    list_rem(l, 50);
    list_rem(l, 10);
    list_rem(l, 1);

    list_print(l);
}
