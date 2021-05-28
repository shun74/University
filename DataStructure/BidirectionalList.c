#include <stdio.h>
#include <stdlib.h>
typedef int Element;

typedef struct node_tag{
    Element value;
    struct node_tag *left, *right;
} Node;

typedef Node *NodePointer;

typedef struct List{
    NodePointer head;
    NodePointer current;
} List;

void Create(List *L){
    L->head = NULL;
    L-> current = NULL;
}

int Size(List *L){
    NodePointer p;
    p = malloc(sizeof(Node));
    p = L->head;
    int count=0;
    while(p!=NULL){
        p = p->right;
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
        p = p->right;
    }
    L->current = p;
    return 1;
}

int FindRight(List *L){
    if(L->current == NULL) return 0;
    else if(L->current->right == NULL) return 0;
    else {
        L->current = L->current->right;
        return 1;
    }
}

int FindLeft(List *L){
    if(L->current == NULL) return 0;
    else if(L->current->left == NULL) return 0;
    else {
        L->current = L->current->left;
        return 1;
    }
}

int InsertRight(List *L, Element e){
    NodePointer p;
    p = malloc(sizeof(Node));
    if(L->head == NULL){
        p->value = e;
        p->right = NULL;
        p->left = NULL;
        L->head = p;
        L->current = p;
        return 1;
    } else {
        p->value = e;
        if(L->current->right==NULL){
            p->right = NULL;
        } else {
            p->right = L->current->right;
            L->current->right->left = p;
        }
        p->left = L->current;
        L->current->right = p;
        L->current = p;
        return 1;
    }
}

int InsertLeft(List *L, Element e){
    NodePointer p;
    p = malloc(sizeof(Node));
    if(L->head == NULL){
        p->value = e;
        p->right = NULL;
        p->left = NULL;
        L->head = p;
        L->current = p;
        return 1;
    } else {
        p->value = e;
        p->left = L->current->left;
        p->right = L->current;
        L->current->left->right = p;
        L->current->left = p;
        L->current = p;
        return 1;
    }
}

int Delete(List *L){
    NodePointer p;
    p = malloc(sizeof(Node));
    if(L->current == NULL) return 0;
    else if(L->head->right == NULL){
        p = L->current;
        L->head = L->current = NULL;
    } else {
        p = L->current;
        if(L->current->left == NULL){
            L->current->right->left = NULL;
            L->head = L->current = L->current->right;
        } else if(L->current->right == NULL){
            L->current->left->right = NULL;
            L->current = L->current->left;
        } else {
            L->current->left->right = L->current->right;
            L->current->right->left = L->current->left;
            L->current = L->current->right;
        }
    }
    free(p);
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
        p = p->right;
    }
    L2->current = q;
}

int Equal(List *L, List *L2 ){
    if(Size(L)!=Size(L2)) return 0;
    NodePointer p,q;
    p = malloc(sizeof(Node));
    q = malloc(sizeof(Node));
    p = L->head;
    q = L2->head;
    while(p!=NULL){
        if(p->value!=q->value) return 0;
        p = p->right;
        q = q->right;
    }
    return 1;
}

void printList(List *L){
    if(L->head==NULL|| L->current==NULL) {
        printf("Empty List\n");
        return;
    }
    NodePointer p;
    p = malloc(sizeof(Node));
    p = L->head;
    printf("Current List: ");
    while(p!=NULL){
        printf("%d ",p->value);
        p = p->right;
    }
    printf("\n");
}

int main(){
    // Check Functions.
    List lst;
    Element a=0;
    Create(&lst);
    // Result of each function -> "Function name + ? + 0or1".
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
    printf("Current value = %d\n", CurPos(&lst));
    printf("Deleted? %d\n", Delete(&lst));
    // &lst: 0->30->20
    printf("Current value = %d\n", CurPos(&lst));
    printList(&lst);

    Element *b;
    b = malloc(sizeof(int));
    printf("Retrieve? %d\n", Retrieve(&lst, b));
    printf("b = %d\n",*b);

    List lst2;
    Create(&lst2);
    Copy(&lst, &lst2);
    printList(&lst2);

    printf("lst lst2 Equal? %d\n",Equal(&lst,&lst2));

    printf("FindLeft? %d\n",FindLeft(&lst));
    printf("Current value = %d\n", CurPos(&lst));

    return 0;
}
