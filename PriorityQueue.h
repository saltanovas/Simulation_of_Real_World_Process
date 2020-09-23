#ifndef PRIORITYQUEUE_H_INCLUDED
#define PRIORITYQUEUE_H_INCLUDED

typedef struct node
{
    double data;
    int priority;
    struct node *next;
} Node;

typedef struct priorityQueue
{
    Node *head;
}PQueue;

// Funkcija kuri sukuria tuscia eile
PQueue* Sukurti()
{
    PQueue *q = (PQueue*) malloc (sizeof(PQueue));
    q->head = NULL;
    return q;
}

// Patikrina ar eile tuscia
int arTuscia(PQueue *q)
{
    if (q->head == NULL)
    {
        return 1;
    }
    else{
        return 0;
    }
}

void idetiElementa(PQueue *q, double data, int priority)
{
    Node* start = q->head;
    Node *tmp = malloc(sizeof(Node));
    if(tmp==NULL)
    {
        printf("Unable to malloc enough space!");
        exit(1);
    }

    tmp->data=data;
    tmp->priority = priority;
    tmp->next=NULL;

    // Cia kai sarasas tuscias
    if (q->head == NULL) {
        q->head = tmp;
        tmp->next = NULL;
    }
    else {
        // tikrininama ar naujo elemento didesnis uz dabart. prio
        if (priority > (q->head)->priority) {
            tmp->next = q->head;
            q->head = tmp;
        }
        // jei ne tada reikia ieskot kurioj vietoj
        else{
          while (start->next != NULL && start->next->priority > priority) {
            start = start->next;
            }
            tmp->next = start->next;
            start->next = tmp;
        }
    }
}

void IstrintiElementa(PQueue *q)
{
    Node* tmp = q->head;
    q->head = q->head->next;
    free(tmp);
}

double paziuretiDidziausia(PQueue *q)
{
    if (q->head == NULL){
        return 0;
    }
    else{
    return q->head->data;
    }
}

void istrintiPrioEile(PQueue *q)
{
    while (q->head != NULL){
        IstrintiElementa(q);
    }
}

void spausdintiPrioEile(PQueue *q)
{
    Node *cursor = q->head;
    while (cursor!=NULL)
    {
        printf(" %.2lf",cursor->data);
        cursor=cursor->next;
    }
    printf("\n");
}

#endif // PRIORITYQUEUE_H_INCLUDED
