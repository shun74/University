#include <stdio.h>
#include <string.h>

void string_copy(char *s, char *l){
    int i=0;
    while(*(s+i) != 0){
        *(l+i) = *(s+i);
        i++;
    }
    *(l+i) = 0;
}


int main(){
    char string[256];
    char copied_string[256];
    scanf("%s",string);
    scanf("%s",copied_string);
    string_copy(string, copied_string);
    printf("original: %s\n",string);
    printf("copied: %s\n",copied_string);

}