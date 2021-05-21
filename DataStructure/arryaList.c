#include <stdio.h>
#define maxsize 1000
typedef int Element;

typedef struct{
    Element value[maxsize];
    int current;
    int last;
} List;

void Creat(List *L){
    L->current = -1;
    L->last = -1;
}

int Size(List *L){
    if(L->last!=-1) return L->last + 1;
    else return -1;
}

int CurPos(List *L){
    return L->current;
}

int Findith(List *L, int i){
    if(i>=0 && i<=(Size(L)-1)){
        L->current = i;
        return 1;
    } else {
        return 0;
    }
}

int FindRight(List *L){
    if(CurPos(L)>=0 && CurPos(L)<=(Size(L)-1)){
        L->current = L->current + 1;
        return 1;
    } else {
        return 0;
    }
}

int FindLeft(List *L){
    if(CurPos(L)>0 && CurPos(L)<=(Size(L)-1)){
        L->current = L->current - 1;
        return 1;
    } else {
        return 0;
    }
}

int InsertRight(List *L, Element e){
    int i;
    if(L->last >= maxsize-1) {
        print("Error: Out of maxsize");
        return 0;
    }
    else if(L->last == -1){
        L->last = 0; L->current = 0;
        L->value[0] = e;
    }
    else if(L->current == -1) return 0;
    else if(L->current == L->last){
        L->current = L->last = L->last+1;
        L->value[L->current] = e;
    }
    else{
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
    if(L->last >= maxsize-1) {
        print("Error: Out of maxsize");
        return 0;
    }
    else if(L->last == -1){
        L->last = 0; L->current = 0;
        L->value[0] = e;
    }
    else if(L->current == -1) return 0;
    else if(L->current == 0){
        L->last = L->last+1;
        for(i=L->last; i>=L->current+1; i--){
            L->value[i] = L->value[i-1];
        }
        L->value[L->current] = e;
    }
    else{
        L->last = L->last+1;
        for(i=L->last; i>=L->current+1; i--){
            L->value[i] = L->value[i-1];
        }
        L->current = L->current + 1;
        L->value[L->current] = e;
    }
    return 1;
}

int Delete(List *L){
    int i;
    if(L->current == -1) return 0;
    else if(L->current != L->last){
        for(i=L->current+1; i<=L->last;i++){
            L->value[i-1] = L->value[i];
        }
        L->last = L->last-1;
    }
    else {
        L->last = L->last-1;
        L->current = -1;
    }
    return 1;
}

int FindeRight(List *L){
    int i;
    if(L-> current == -1) return 0;
    else if(L->current >= L->last) return 0;
    else{
        L->current >= L->current+1;
    return 1;
    }
}
