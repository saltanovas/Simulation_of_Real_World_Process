#ifndef QUEUE_H_INCLUDED
#define QUEUE_H_INCLUDED
#include <stdlib.h>

struct List
{
    double data;
    struct List* next;
};

struct Queue
{
    struct List* first, * last;
};

struct Queue* createQueue()
{
    struct Queue* x;
    x = (struct Queue*) malloc(sizeof(struct Queue));
    x->first = NULL;
    x->last = NULL;
    return x;
}

int isEmpty(struct Queue* x)
{
    if (x->first == NULL)
        return 1;
    else
        return 0;
}

int isFull(struct Queue* x)
{
    if (x == NULL)
        return 1;
    else
        return 0;
}

void enqueue(struct Queue* x, double value)
{
    struct List* elem;
    elem = (struct List*) malloc(sizeof(struct List));
    if (isFull(x))
    {
        printf("Queue is full!");
        return;
    }

    elem->data = value;
    elem->next = NULL;

    if (x->first == NULL)
    {
        x->first = elem;
        x->last = elem;
    }

    else
    {
        x->last->next = elem;
        x->last = elem;
    }
}

void dequeue(struct Queue* x)
{
    if (isEmpty(x))
        return;

    struct List* temp;
    temp = x->first;

    x->first = x->first->next;

    free(temp);
}

double firstElement(struct Queue* x)
{
    if (isEmpty(x))
        return 0; // zero here is for false
    return (x->first->data);
}

int amountOfData(struct Queue* x)
{
    int amount = 0;

    struct List* temp;
    temp = x->first;

    while (temp != NULL)
    {
        temp = temp->next;
        amount++;
    }
    return amount;
}

void removeQueue(struct Queue* x)
{
    struct List* temp;

    while (x->first)
    {
        temp = x->first;
        x->first = x->first->next;
        free(temp);
    }
}

void outputQueue(struct Queue* x)
{
    if (isEmpty(x))
    {
       // printf("Queue is empty!\n");
        return;
    }

    struct List* temp;
    temp = x->first;

    do
    {
        printf("%.2lf ", temp->data);
        temp = temp->next;
    } while (temp != NULL);
    printf("\n");
}

#endif // QUEUE_H_INCLUDED
