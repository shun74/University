#include <stdio.h>
//'a' - 'A' = 32
void caps(int n, char *p){
    *(p+n) -= 32;
}

int main(){
   char s[7];
   scanf("%s",s);
    for(int i=0; i<6; i++){
        caps(i,s);
        printf("%s\n", s);
    }
}