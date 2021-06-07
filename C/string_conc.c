#include <stdio.h>
#include <string.h>

/*19行目を消すと入力によっては動作がおかしくなります。
予約しているメモリに先に謎の文字が入っていたりします(?)。
詳しくは実行結果を参照*/
void conbine(int s_n, int l_n, char *s, char *l, char *conb){
    for(int i=0; i<s_n; i++){
        *(conb+i) = *(s+i);
        printf("%p\n", conb+i);
        // printf("size:%d\n", sizeof(*(conb+i)));
    }
    for(int i=0; i<l_n; i++){
        *(conb+s_n+i) = *(l+i);
        printf("%p\n", conb+s_n+i);
        // printf("size:%d\n", sizeof(*(conb+s_n+i)));
    }
    for(int i=0; i<20;i++){
        printf("%p:%c\n",conb+s_n+l_n+i,*(conb+s_n+l_n+i));
    }
    *(conb+s_n+l_n) = 0;
}

int main(){
    char s[129];
    char l[129];
    char conb[257];
    int s_n=0,l_n=0;
    scanf("%s", s);
    scanf("%s", l);
    s_n = strlen(s);
    l_n = strlen(l);
    printf("s_n:%d l_n:%d\n", s_n, l_n);
    conbine(s_n, l_n, s, l, conb);
    printf("s:%s\n",s);
    printf("l:%s\n",l);
    // printf("%d", conb[s_n+l_n]);
    printf("conb:%s\n",conb);
}