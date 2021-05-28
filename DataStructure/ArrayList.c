#include <stdio.h>
#include <stdlib.h>
typedef int Element;
#define maxsize 1000

typedef struct{
    Element value[maxsize];
    int current;
    int last;
} List;

void Create(List *L){
    L->current = -1;
    L->last = -1;
}

int Size(List *L){
    if(L->last == -1) return 0;
    return L->last+1;
}

int CurPos(List *L){
    if(L->current==-1) {
        printf("Current Undefined\n");
        return -1;
    }
    return L->value[L->current];
}

int Findith(List *L, int i){
    if(L->last==-1 || Size(L)-1<i) return 0;
    L->current = i;
    return 1;
}

int FindRight(List *L){
    int i;
    if(L->current==-1 || L->current==L->last) return 0;
    L->current = L->current+1;
    return 1;
}

int FindLeft(List *L){
    int i;
    if(L->current==-1 || L->current==0) return 0;
    L->current = L->current-1;
    return 1;
}

int InsertRight(List *L, Element e){
    int i;
    if(L->last >= maxsize-1){
        printf("List is full\n");
        return 0;
    } else if(L->last == -1){
        L->last = 0;
        L->current = 0;
        L->value[0] = e;
    } else if(L->current == -1) return 0;
    else if(L->current == L->last){
        L->current = L->last = L->last+1;
        L->value[L->current] = e;
    } else{
        L->last = L->last+1;
        for(i=L->last; i>=L->current+2; i--){
            L->value[i] = L->value[i-1];
        }
        L->current = L->current + 1;
        L->value[L->current] = e;
    }
    return 1;
}

int InsertLeft(List *L, Element e){
    int i;
    if(L->last >= maxsize-1){
        printf("List is full\n");
        return 0;
    } else if(L->last == -1){
        L->last = 0;
        L->current = 0;
        L->value[0] = e;
    } else if(L->current == -1) return 0;
    else if(L->current == 0){
        L->last = L->last+1;
        for(i=L->last; i>=L->current+1; i--){
            L->value[i] = L->value[i-1];
        }
        L->value[L->current] = e;
    } else{
        L->last = L->last+1;
        for(i=L->last; i>=L->current; i--){
            L->value[i] = L->value[i-1];
        }
        L->value[L->current] = e;
    }
    return 1;
}

int Delete(List *L){
    int i;
    if(L->current == -1) return 0;
    else if(L->current != L->last){
        for(i=L->current+1; i<=L->last; i++){
            L->value[i-1] = L->value[i];
        }
        L->last = L->last -1;
        return 1;
    } else {
        L->last = L->last -1;
        L->current = -1;
        return 1;
    }
}

int Retrieve(List *L, Element *v){
    if(L->current == -1) return 0;
    else {
        *v = L->value[L->current];
        return 1;
    }
}

int Update(List *L, Element e){
    if(L->current==-1) return 0;
    else {
        L->value[L->current] = e;
        return 1;
    }
}

void Copy(List *L, List *L2 ){
    for(int j=0;j<L->last+1;j++){
        InsertRight(L2, L->value[j]);
    }
    L2->current = L->current;
}

int Equal(List *L, List *L2 ){
    if(Size(L)!=Size(L2)) return 0;
    for(int j=0;j<L->last+1;j++){
        if(L->value[j]!=L2->value[j]) return 0;
    }
    return 1;
}

void printList(List *L){
    if(L->current==-1 || L->last==-1) {
        printf("Empty List\n");
        return;
    }
    printf("Current List: ");
    for(int j=0;j<=L->last;j++){
        printf("%d ",L->value[j]);
    }
    printf("\n");
    return;
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
