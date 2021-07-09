#include <stdio.h>
#include <stdlib.h>

typedef struct obj {
    int a;
    void (*add)();
    int (*get)();
}OBJ;

void add(OBJ *o, int x){
    int i = o->a;
    o->a = i + x;
}

int get(OBJ *o){
    return o->a;
}

OBJ *new_OBJ(int x) {
    OBJ *o = (OBJ*)malloc(sizeof (struct obj));
    o->add = add;
    o->get = get;
    o->a = x;
    return o;
}

/* Dispatcher */
#define offsetof(type, member) ((size_t)&((type*)0)->member)
int send(OBJ *o, size_t offset, int x){
    void (*f) ();
    f = *((void**)((char *)o + offset));
    (*f) (o,x);
}

int main(){
    OBJ *o = new_OBJ(0);
    o->add(o, 5);
    o->add(o, 7);

    send(o, offsetof(OBJ, add), 3);

    printf("%d\n", o->get(o));
}