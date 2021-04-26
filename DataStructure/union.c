#include <stdio.h>

int main(void){
    typedef struct s{
        int a;
        char c;
    }S;
    typedef union u{
        int a;
        char c;
    }U;

    S b;
    U d;

    b.a = 10;
    b.c = 'c';

    d.a = 10;
    d.c = 'd';
    printf("struct %d %c\n", b.a, b.c);
    printf("union %d %c\n", d.a, d.c);
}
