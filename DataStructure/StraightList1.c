#include <stdio.h>
#include <stdlib.h>
typedef int Element;

typedef struct node_tag{
    Element value;
    struct node_tag *next;
} Node;

typedef Node *NodePointer;

typedef struct{
    NodePointer head;
    NodePointer current;
} List;

void Create(List *L){
    L -> head = NULL;
    L -> current = NULL;
    printf("Created\n");
}

int Size(List *L){
    struct node_tag *N;
    N = malloc(sizeof(Node));
    N = L->head;
    int count=0;
    while(N!=NULL){
        N = N->next;
        count++;
    }
    return count;
}

int CurPos(List *L){
    struct node_tag *N;
    N = malloc(sizeof(Node));
    N = L->current;
    if(N->value){
        return N->value;
    } else {
        return -1;
    }
}

int Findith(List *L, int i){
    if(L->head==NULL){
        return 0;
    }
    struct node_tag *N;
    N = malloc(sizeof(Node));
    N = L->head;
    for(int i=0; i<i; i++){
        if(N==NULL) return 0;
        N = N->next;
    }
    L->current = N;
    return 1;
}

int FindRight(List *L){
    if(L->current == NULL) return 0;
    else if(L->current->next == NULL) return 0;
    else {
        L->current = L->current->next;
        return 1;
    }
}

int InsertRight(List *L, Element e){
    NodePointer p;
    if(L->head == NULL){
        p = malloc(sizeof(Node));
        p->value = e;
        p->next = NULL;
        L->head = p;
        L->current = p;
        return 1;
    }
    else if(L->current==NULL) return 0;
    else {
        p = malloc(sizeof(Node));
        p->value = e;
        p->next = L->current->next;
        L->current->next = p;
        L->current = p;
        return 1;
    }
}

int FindLeft(List *L){
    NodePointer p,q;
    if(L->current == NULL) return 0;
    else if(L->current == L->head) return 0;
    else{
        p = L->current;
        q = L->head;
        while(q->next != p) q = q->next;
        L->current = q;
        return 1;
    }
}

int Retrieve(List *L, Element *v){
    if(L->current == NULL) return 0;
    else {
        *v = L->current->value;
        return 1;
    }
}

int Update(List *L, Element e){
    if(L->current == NULL) return 0;
    else {
        L->current->value = e;
        return 1;
    }
}
