#include <stdio.h>

void square(int a){
    a = a * a;
    printf("Pointer a:%p, Squared a:%d\n",&a, a);
}

void squareP(int *b){
    *b = *b * *b;
    printf("Pointer b:%p, Squared b:%d\n",b, *b);
}

int main(){
    int a = 9;
    int b = 8;
    //aはポインタが違っていてbは同じポインタになっている.
    //%pはポインタの指定子
    printf("Pointer a:%p, a:%d\n",&a, a);
    printf("Pointer b:%p, b:%d\n",&b, b);
    square(a);
    squareP(&b);
}