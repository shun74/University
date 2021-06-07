#include <stdio.h>
#include <string.h>

int string_length(char *s){
    int i=0;
    while(*(s+i) != 0){
        i++;
    }
    return i;
}


int main(){
    char string[256];
    scanf("%s",string);
    int len = string_length(string);
    printf("%d\n",len);
}