#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(){
    int a;
    int *ptr;
    ptr = (int *)malloc(sizeof(int));
    printf( "Input an integer:\n" );
    scanf("%d", &a);
    *ptr = a;

    printf("%d\n", *ptr);
    free(ptr);
}