#include <stdio.h>

void swap(int a, int b, char *s){
    char tmp;
    tmp = s[a-1];
    s[a-1] = s[b-1];
    s[b-1] = tmp;
}

int main(){
    int a,b;
    char s[256];
    printf("Input string>");
    scanf("%s", &s);
    scanf("%d %d", &a, &b);
    swap(a,b,s);
    printf("%s\n", s);
}