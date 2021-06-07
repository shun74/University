#include <stdio.h>
#include <string.h>
#define DIFFERNCE 32 //(a - A)

void caps3(char *s){
    int i = 0;
    while(*(s+i) != 0){
        if(*(s+i)>='a' && *(s+i)<='z') *(s+i) -= DIFFERNCE;
        else if(*(s+i)>='A' && *(s+i)<='Z') *(s+i) += DIFFERNCE;
        i++;
    }
}

int main(){
    char string[256];
    scanf("%s",string);
    caps3(string);
    printf("%s\n",string);
}