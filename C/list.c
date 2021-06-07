#include <stdio.h>
#include <stdlib.h>

struct cell{
    int item;
    struct cell *next;
};

void printList(struct cell *c){
    printf("%d ",c->item);
    if((c->next)!=NULL) return printList(c->next);
    else {
        printf("\n");
        return;
    }
}

struct cell * next(struct cell *c){
    return c -> next;
}

struct cell * tail(struct cell *c){
    if(c->next != NULL) {
        return tail(c->next);
    } else {
        return c;
    }
}

struct cell * push(int n, struct cell *plist){
    struct cell *c;
    c = malloc(sizeof(struct cell));
    c->item = n;
    c->next = plist;
    return c;
}

struct cell * pop(struct cell *plist){
    struct cell *c;
    c = malloc(sizeof(struct cell));
    c = plist->next;
    free(plist);
    return c;
}

struct cell * copy(struct cell *plist){
    struct cell *c;
    c = malloc(sizeof(struct cell));
    if(plist->next == NULL){
        c->item = plist->item;
        c->next = NULL;
        return c;
    } else {
        c->item = plist->item;
        c->next = copy(plist->next);
        return c;
    }
}

struct cell * reverse(struct cell *plist){
    struct cell *c;
    c = malloc(sizeof(struct cell));
    c = NULL;
    while(plist != NULL){
        c = push(plist->item, c);
        plist = plist->next;
    }
    return c;
}

struct cell * nconc(struct cell *plist1, struct cell *plist2){
    tail(plist1)->next = plist2;
    return plist1;
}

struct cell * append(struct cell *plist1, struct cell *plist2){
    struct cell *c1;
    c1 = malloc(sizeof(struct cell));
    struct cell *c2;
    c2 = malloc(sizeof(struct cell));
    
    c1 = copy(plist1);
    c2 = copy(plist2);

    tail(c1)->next = c2;
    return c1;
    
}

int main(){
   struct cell *pl,*res;

    pl=NULL;
    pl = push(3,pl);
    pl = push(2,pl);
    pl = push(1,pl);

    printList(pl);

    res = reverse(pl);
    printList(res);
    printList(pl);

}