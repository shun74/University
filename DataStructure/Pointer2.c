#include <stdio.h>

int main(){
    typedef struct r {
        int num1;
        float num2;
    }R;

    R b, *pb;
    b.num1 = 1;
    b.num2 = 2.0;
    pb = &b;
    //%pはポインタの指定子
    printf("b pointer %p\n", pb);
    //同じ値になる
    printf("(*pb).num1: %d, (*pb).num2: %f\n", (*pb).num1, (*pb).num2);
    printf("pb -> num1: %d, pb -> num2: %f\n", pb -> num1, pb -> num2);

}