#include <stdio.h>

int main(){
    char s[8];
    s[0] = 'a';
    s[1] = 'b';
    s[2] = 'c';
    s[3] = 'd';
    s[4] = 'e';
    s[5] = 'f';
    s[6] = 'g';
    char *p;
    p = &(s[0]);
    printf("%s\n",s);
    for(int i=0;i<7;i++){
        //'a' - 'A' = 32
        *p -= 32;
        p++;
        printf("%s\n",s);
    }
}