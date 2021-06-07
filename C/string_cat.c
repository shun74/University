#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *concat(char *s, char *l, char *conc){
    while(*s!=0){
        *conc = *s;
        s++;
        conc++;
    }
    while(*l!=0){
        *conc = *l;
        l++;
        conc++;
    }
    // *conc = 0;
}

int main(){
    char s[256];
    char l[256];
    char *conc;

    scanf("%s", s);
    scanf("%s", l);
    
    conc = (char *)malloc( sizeof(char) * (strlen(s)+strlen(l) - 7) );
    printf("%p\n",conc);//毎回変わる
    concat(s,l,conc);

    printf("%s", conc);

    free(conc);
}