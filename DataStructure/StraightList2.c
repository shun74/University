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
    NodePointer p;
    p = malloc(sizeof(Node));
    p->next = NULL;
    L->head = p;
    L->current = NULL;
}

int Size(List *L){
    NodePointer p;
    p = malloc(sizeof(Node));
    p = L->head;
    int count=0;
    while(p!=NULL){
        p = p->next;
        count++;
    }
    return count;
}

int CurPos(List *L){
    NodePointer p;
    p = malloc(sizeof(Node));
    p = L->current;
    if(p->value || p->value==0){
        return p->value;
    } else {
        return -1;
    }
}

int Findith(List *L, int i){
    if(L->head==NULL){
        return 0;
    }
    NodePointer p;
    p = malloc(sizeof(Node));
    p = L->head;
    for(int j=0; j<i; j++){
        if(p==NULL) return 0;
        p = p->next;
    }
    L->current = p;
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

int InsertRight(List *L, Element e){
    NodePointer p;
    p = malloc(sizeof(Node));
    if(L->head == NULL){
        p->value = e;
        p->next = NULL;
        L->head = p;
        L->current = p;
        return 1;
    } else {
        p->value = e;
        p->next = L->current->next;
        L->current->next = p;
        L->current = p;
        return 1;
    }
}

int InsertLeft(List *L, Element e){
    NodePointer p;
    if(L->head == NULL){
        p = malloc(sizeof(Node));
        p->value = e;
        p->next = NULL;
        L->head = p;
        L->current = p;
        return 1;
    }
    else {
        p = malloc(sizeof(Node));
        p->value = e;
        NodePointer q;
        q = malloc(sizeof(Node));
        q = L->head;
        while(q->next != L->current){
            q = q->next;
        }
        q->next = p;
        p->next = L->current;
        L->current = p;
        return 1;
    }
}

int Delete(List *L){
    if(L->current== NULL ) return 0;
    NodePointer q;
    q = malloc(sizeof(Node));
    q = L->head;
    if (L->current == L->head){
        free(L->current);
        L->head = NULL;
        L->current = NULL;
    } else if (L->current->next == NULL){
        while(q->next != L->current){
            q = q->next;
        }
        free(L->current);
        L->current = q;
    } else {
        while(q->next != L->current){
            q = q->next;
        }
        q->next = L->current->next;
        free(L->current);
        L->current = q->next;
    }
    return 1;
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

void Copy( List *L, List *L2 ){
    NodePointer p,q;
    p = malloc(sizeof(Node));
    q = malloc(sizeof(Node));
    p = L->head;
    while(p!=NULL){
        InsertRight(L2, p->value);
        if(L->current==p){
            q = L2->current;
        }
        p = p->next;
    }
    L2->current = q;
}

int Equal( List *L, List *L2 ){
    if(Size(L)!=Size(L2)) return 0;
    NodePointer p,q;
    p = malloc(sizeof(Node));
    q = malloc(sizeof(Node));
    p = L->head;
    q = L2->head;
    while(p!=NULL){
        if(p->value!=q->value) return 0;
        p = p->next;
        q = q->next;
    }
    return 1;
}

void printList(List *L){
    if(L->head == NULL|| L->current==NULL) {
        printf("Empty List\n");
        return;
    }
    NodePointer p;
    p = malloc(sizeof(Node));
    p = L->head;
    printf("Current List: ");
    while(p!=NULL){
        printf("%d ",p->value);
        p = p->next;
    }
    printf("\n");
}

int main(){
    // Check Functions.
    
    return 0;
}
