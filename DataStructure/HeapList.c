#include <stdio.h>
#include <stdlib.h>
#define NULL -1
#define maxsize 100

typedef int NodePointer;
typedef int Element;

typedef struct{
NodePointer head;
NodePointer current;
} List;

typedef struct {
Element value;
NodePointer next;
} Node;

Node Heap[maxsize];
NodePointer FREE;

void HeapInit(){
    NodePointer i;
    FREE = 0;
    for(i=0;i<maxsize-1;i++){
        Heap[i].next = i+1;
    }
    Heap[maxsize-1].next = -1;
}

int Malloc(){
    NodePointer p;
    if(FREE == NULL) printf("No Free Space.\n");
    else {
        p = FREE;
        FREE = Heap[FREE].next;
    }
    return p;
}

void Free(NodePointer p){
    Heap[p].next = FREE;
    FREE = p;
}

void Create(List *L){
    NodePointer p;
    p = Malloc();
    Heap[p].next = NULL;
    L->head = p;
    L->current = NULL;
}

int Size(List *L){
    NodePointer p;
    p = Malloc();
    p = Heap[L->head].next;
    int count=0;
    while(p!=NULL){
        p = Heap[p].next;
        count++;
    }
    return count;
}

int CurPos(List *L){
    NodePointer p;
    p = Malloc();
    p = Heap[L->current].next;
    if(Heap[p].value || Heap[p].value==0){
        return Heap[p].value;
    } else {
        return -1;
    }
}

int Findith(List *L, int i){
    if(Heap[L->head].next==NULL){
        return 0;
    }
    NodePointer p;
    p = Malloc();
    p = L->head;
    for(int j=0; j<i; j++){
        if(p==NULL) return 0;
        p = Heap[p].next;
    }
    L->current = p;
    return 1;
}

int FindRight(List *L){
    if(Heap[L->head].next==NULL || L->current==NULL) return 0;
    else {
        L->current = Heap[L->current].next;
        return 1;
    }
}

int FindLeft(List *L){
    NodePointer p, q;
    if(L->current == NULL) return 0;
    else if(L->current == L->head) return 0;
    else {
        p = L->current;
        q = L->head;
        while (Heap[q].next != p){
            q = Heap[q].next;
        }
        L->current = q;
        return 1;
    }
}

int InsertRight(List *L, Element e){
    NodePointer p;
    p = Malloc();
    if(Heap[L->head].next == NULL){
        Heap[p].value = e;
        Heap[p].next = NULL;
        Heap[L->head].next = p;
        L->current = Heap[L->head].next;
        return 1;
    } else if(Heap[L->current].next==NULL){
        Heap[p].value = e;
        Heap[p].next = NULL;
        Heap[L->current].next = p;
        return 1;
    } else {
        Heap[p].value = e;
        Heap[p].next = Heap[Heap[L->current].next].next;
        Heap[Heap[L->current].next].next = p;
        return 1;
    }
}

int InsertLeft(List *L, Element e){
    NodePointer p;
    if (L->current == NULL){
        if(Heap[L->head].next != NULL) return 0;
        else {
            p = Malloc();
            Heap[p].value = e;
            Heap[p].next = NULL;
            Heap[L->head].next = p;
            L->current = Heap[L->head].next;
            return 1;
        }
    } else {
        p = Malloc();
        Heap[p].value = e;
        Heap[p].next = Heap[L->current].next;
        Heap[L->current].next = p;
        return 1;
    }
}

int Delete(List *L){
    NodePointer p;
    if(L->current == NULL) return 0;
    else {
        p = Heap[L->current].next;
        Heap[L->current].next = Heap[p].next;
        Free(p);
    }
    if(Heap[L->current].next ==NULL) {
        L->current = NULL;
    }
    return 1;
}

int Retrieve(List *L, Element *v){
    if(L->current==NULL || Heap[L->current].next==NULL) return 0;
    else {
        *v = Heap[Heap[L->current].next].value;
        return 1;
    }
}

int Update(List *L, Element e){
    if(L->current==NULL || Heap[L->current].next==NULL) return 0;
    else {
        Heap[Heap[L->current].next].value = e;
        return 1;
    }
}

int Equal(List *L, List *L2 ){
    if(Size(L)!=Size(L2)) return 0;
    NodePointer p,q;
    p = Malloc();
    q = Malloc();
    p = Heap[L->head].next;
    q = Heap[L2->head].next;
    while(p!=NULL){
        if(Heap[p].value!=Heap[q].value) return 0;
        p = Heap[p].next;
        q = Heap[q].next;
    }
    return 1;
}

void printList(List *L){
    if(L->head == NULL || L->current==NULL) {
        printf("Empty List\n");
        return;
    }
    NodePointer p;
    p = Malloc();
    p = Heap[L->head].next;
    printf("Current List: ");
    while(p!=NULL){
        printf("%d ",Heap[p].value);
        p = Heap[p].next;
    }
    printf("\n");
}

int main(){
    // Check Functions.
    HeapInit();

    List lst;
    Create(&lst);
    // Result of each function -> "Function name + ? + 0or1".
    Element a=0;
    printf("Insert? %d\n",InsertRight(&lst, a));
    a=10;
    printf("Insert? %d\n",InsertRight(&lst, a));
    a=20;
    printf("Insert? %d\n",InsertRight(&lst, a));
    printf("Size = %d\n", Size(&lst));
    printList(&lst);
    // &lst: 0->10->20
    printf("Findith? %d\n",Findith(&lst, 1));
    // current = 1, value = 10.
    printf("Current value = %d\n", CurPos(&lst));
    a=30;
    printf("Insert? %d\n",InsertLeft(&lst, a));
    // &lst: 0->30->10->20
    printf("Current value = %d\n", CurPos(&lst));
    printList(&lst);

    printf("FindRight? %d\n",FindRight(&lst));
    printf("Deleted? %d\n", Delete(&lst));
    // &lst: 0->30->20
    printList(&lst);

    Element *b;
    b = malloc(sizeof(int));
    printf("Retrieve? %d\n", Retrieve(&lst, b));
    printf("b = %d\n",*b);

    List lst2;
    Create(&lst2);
    //Copy lst1->lst2
    InsertRight(&lst2,0);
    InsertRight(&lst2,30);
    InsertRight(&lst2,20);
    printList(&lst2);

    printf("lst lst2 Equal? %d\n",Equal(&lst,&lst2));

    printf("FindLeft? %d\n",FindLeft(&lst));
    printf("Current value = %d\n", CurPos(&lst));

    return 0;
}
