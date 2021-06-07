#include <stdio.h>
#include <string.h>
#define DIFFERNCE 32 //(a - A)

void caps2(char *s){
    int i = 0;
    while(*(s+i) != 0){
        *(s+i) -= DIFFERNCE;
        printf("%s\n",s);
        i++;
    }
}

int main(){
    char string[256];
    scanf("%s",string);
    caps2(string);
}