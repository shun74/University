#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(){
    char s[256];
    char *ptr;
    int i=0;
    while( scanf("%s", s) != EOF){
        i = 0;
        ptr = (char *)malloc(sizeof(char) * (strlen(s)+1));
        while(s[i]){
            ptr[i] = s[i];
            i++;
        }
        ptr[i] = 0;
        printf("%s\n", ptr);

        free(ptr);
    }
}