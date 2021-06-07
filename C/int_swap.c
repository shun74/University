#include <stdio.h>
#include <string.h>

void swap(int *a, int *b){
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

int main(){
    int a,b;
    a = 100;
    b = 200;

    printf("before: a = %d, b = %d\n", a, b);
    swap(&a,&b);
    printf("after: a = %d, b = %d\n", a, b);
}