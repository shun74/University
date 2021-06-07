#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define maxsize 1000
typedef char Element;

typedef struct{
    int top;
    Element value[maxsize];
}Stack;

void Create(Stack *S){
    S->top = maxsize-1;
}

int Empty(Stack *S){
    if(S->top==maxsize) return 1;
    return 0;
}

int PushDown(Stack *S, Element e){
    if(S->top==0) return 0;
    else {
        S->top = S->top-1;
        S->value[S->top] = e;
        return 1;
    }
}

int PopUp(Stack *S){
    if(Empty(S)) return 0;
    else {
        S->top = S->top + 1;
        return 1;
    }
}

int Retrieve(Stack *S, Element *v){
    if(Empty(S)) return 0;
    else {
        *v = S->value[S->top];
        return 1;
    }
}

void Edit(){
    Stack S, T;
    Element e;
    char c;
    Create(&S);
    do{
        scanf("%c", &c);
        if(c == '#'){
            if(!PopUp(&S)){
                printf("PopUp Error\n");
                return;
            }
        }
        else if (c == '@'){
            Create(&S);
        } else {
            if(!PushDown(&S, c)){
                printf("PushDown Error");
                return;
            }
        }
    } while(c!='\n');
    Create(&T);
    while(!Empty(&S)){
        PushDown( &T, (Retrieve(&S, &e), e ));
        PopUp(&S);
    }
    PopUp(&T);
    while(!Empty(&T)){
        Retrieve(&T, &e);
        printf("%c",e);
        PopUp(&T);
    }
}

void Calculate(char *s){
    Stack T;
    Create(&T);
    while(*s!=0){
        if(*s=='+'){
            char a,b;
            int c;
            Retrieve(&T,&a);
            PopUp(&T);
            Retrieve(&T,&b);
            PopUp(&T);
            c = (int)a + (int)b;
            PushDown(&T,(char)c);
            printf("Push %d + %d \n",(int)a,(int)b);
        }
        else if(*s=='-'){
            char a,b;
            int c;
            Retrieve(&T,&a);
            PopUp(&T);
            Retrieve(&T,&b);
            PopUp(&T);
            c = (int)a - (int)b;
            PushDown(&T,(char)c);
            printf("Push %d - %d \n",(int)a,(int)b);
        }
        else if(*s=='*'){
            char a,b;
            int c;
            Retrieve(&T,&a);
            PopUp(&T);
            Retrieve(&T,&b);
            PopUp(&T);
            c = (int)a * (int)b;
            PushDown(&T,(char)c);
            printf("Push %d * %d \n",(int)a,(int)b);
        }
        else if(*s=='/'){
            char a,b;
            int c;
            Retrieve(&T,&a);
            PopUp(&T);
            Retrieve(&T,&b);
            PopUp(&T);
            c = (int)a / (int)b;
            PushDown(&T,(char)c);
            printf("Push %d / %d \n",(int)a,(int)b);
        } else {
            PushDown(&T,(char)(*s-'0'));
            printf("Push %c \n",*s);
        }
        s++;
    }
    char a;
    Retrieve(&T, &a);
    printf("Answer %d\n",a);
}

int main(){
    // Caluculate:入力は1桁のみで記法は逆ポーランド記法です。
    char s[256];
    strcpy(s,"12+34+*");
    printf("%s\n",s);
    Calculate(s);
    strcpy(s,"12+34+-12+34+**");
    printf("%s\n",s);
    Calculate(s);
    printf("Edit:");
    Edit();
}
