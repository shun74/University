#include <stdio.h>
//'a' - 'A' = 32
void convert(int n, char *p){
    if(*(p+n)>='a' && *(p+n)<='z'){
        *(p+n) -= 32;
    } else if(*(p+n)>='A' && *(p+n)<='Z'){
        *(p+n) += 32;
    }
}

int main(){
    char s[7];
    scanf("%s", s);
    printf("%s\n", s);
    for(int i=0; i<6; i++){
        convert(i,s);
    }
    printf("%s\n", s);
}