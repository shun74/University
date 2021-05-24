#include <stdio.h>

int main(){
    typedef struct r {
        int num1;
        float num2;
    }R;
    
    typedef union u {
        int num1;
        float num2;
    }U;
    
    R b;
    U c;

    b.num1 = 1;
    c.num1 = 0;
    printf("%d, %d\n", b.num1,c.num1);
    b.num2 = 3.0;
    c.num2 = 4.0;
    //c.num1の値がおかしくなる
    printf("b.num1:%d  b.num2:%f\nc.num1:%d c.num2:%f",b.num1, b.num2, c.num1, c.num2);
}