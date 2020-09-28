#include <stdlib.h>
#include <stdio.h>
#include "linked_list.h"

list_t list_create()
{
    struct list * list_t = (struct list *) malloc(sizeof(list_t));
    /* list_t->head = NULL; */
    /* list_t->tail = NULL; */
    list_t->length = 0;
    return list_t;
}

void list_delete(list_t list)
{
    if (list->length == 1)
    {
        free(list->head);
        free(list->tail);
        free(list);
    }

    else
    {
        free(list->head);
        free(list->tail);
        free(list);
    }
    /* int i; */
    /* for (i = 1; i < list->length; i++) */
    /* { */
    /*     free() */
    /* } */
    /* if (list->length == 1) */
    /* { */
    /*     free() */
    /* } */
    /* free(list); */
}

void list_insert(list_t list, int index, int data)
{
    struct node * mynode;
    mynode = (struct node *) malloc(sizeof(struct node));

    struct node * tempnode = list->head;
    /* tempnode = (struct node *) malloc(sizeof(struct node)); */
    /* tempnode = list->head; */

    int i;
    for (i = 0; i < index-1; i++)
    {

        tempnode = tempnode->next;

    }
    mynode->data = data;
    mynode->next = tempnode->next;
    mynode->prev = tempnode;
    if (tempnode->next != NULL)
    {
        tempnode->next->prev = mynode;
    }
    tempnode->next = mynode;

}

void list_append(list_t list, int data)
{
    struct node * mynode = NULL;
    mynode = (struct node *) malloc(sizeof(struct node));
    mynode->data = data;
    if (list->length == 0)
    {
        mynode->prev = NULL;
        mynode->next = NULL;
        list->length++;
        list->head = mynode;
    }
    else if (list->tail == NULL)
    {
        mynode->prev = list->head;
        mynode->next = NULL;
        list->head->next = mynode;
        list->length++;
        list->tail = mynode;
    }
    else
    {
        mynode->prev = list->tail;
        mynode->next = NULL;
        list->tail->next = mynode;
        list->tail = mynode;
        list->length++;
    }
}

void list_print(list_t list)
{
    struct node * mynode = list->head;
    /* mynode = (struct node *) malloc(sizeof(struct node)); */

    /* mynode = list->head; */

    while (mynode != NULL)
    {
        printf("%i\n", mynode->data);
        mynode = mynode->next;
    }
}

long list_sum(list_t list)
{
    int i;
    long sum = 0;
    struct node * tempnode = list->head;
    /* tempnode = (struct node *) malloc(sizeof(struct node)); */
    /* tempnode = list->head; */

    for(i = 0; i < list->length; i++)
    {
        sum += tempnode->data;
        tempnode = tempnode->next;
    }
    return sum;
}

int list_get(list_t list, int index)
{
    struct node * mynode = list->head;
    /* mynode = (struct node *) malloc(sizeof(struct node)); */
    /* mynode = list->head; */

    int i;
    for (i = 0; i < index; i++)
    {
        mynode = mynode->next;
    }
    return mynode->data;
}

int list_extract(list_t list, int index)
{
    struct node * mynode = list->head;
    /* mynode = (struct node *) malloc(sizeof(struct node)); */
    /* mynode = list->head; */
    int temp;

    if(list->length == 0)
    {
        temp = mynode->data;
        free(mynode->prev); /* these should be freeing NULL pointers */
        free(mynode->next);
    }

    else if(index == 0)
    {
        list->head = list->head->next;
        list->head->prev = NULL;
        temp = mynode->data;
    }
    else
    {
        int i;
        for (i = 0; i < index; i++)
        {
            mynode = mynode->next;
        }

        if (mynode->next == NULL)
        {
            list->tail = mynode;
            list->tail->next = NULL;
            temp = mynode->data;
        }

        else
        {
            mynode->prev->next = mynode->next;
            mynode->next->prev = mynode->prev;
            temp = mynode->data;
        }
    }
    free(mynode);
    list->length -= 1;
    return temp;
}
