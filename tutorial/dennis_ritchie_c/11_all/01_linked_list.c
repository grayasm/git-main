/* Mihai: implement a simple linked list in C.
 */
#include <stdio.h>
#include <stdlib.h>


struct node {
    struct node *next;
    int val;
};

struct list {
    struct node *head;
};

void list_init(struct list **l)
{
    if(*l != NULL)
        return;
    *l = (struct list*)malloc(sizeof (struct list));
    (*l)->head = NULL;
}

void list_clean(struct list *l)
{
    if(l == NULL)
        return;
    struct node *n = l->head, *m = NULL;
    while (n)
    {
        m = n->next;
        free(n);
        n = m;
    }
    l->head = NULL;
}

void list_add(struct list *l, int v)
{
    struct node *n;

    if (l->head == NULL) {
        l->head = (struct node*) malloc(sizeof (struct node));
        l->head->val = v;
        l->head->next = NULL;
    }
    else {
        n = l->head;
        while (n && n->next)
            n = n->next;
        n->next = (struct node*) malloc(sizeof (struct node));
        n = n->next;
        n->val = v;
        n->next = NULL;
    }
}

void list_print(struct list *l)
{
	struct node *n;

    printf ("printing a list\n");
    n = l->head;
    while (n) {
        printf("%d\n", n->val);
        n = n->next;
    }
}

main()
{
    struct list *l = NULL;
    list_init(&l);

    list_add(l, 1);
    list_add(l, 2);
    list_add(l, 10);
    list_add(l, 0);

    list_print(l);

    list_clean(l);
    list_print(l);
}
