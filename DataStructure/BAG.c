#include <stdio.h>
#define maxsize = 100

int main(){
    typedef struct b{
        int value[maxsize];
        int size;
    }BAG;

    BAG insert(int e, BAG B){

    }

    int search(int e, BAG *B){
        int i=0;
        while((B->value[i] != e) && (i <= B->size)) i=i+1;
        if(i<=B->size) return i;
        else return -1;
    }

    BAG delete(int e, BAG B){
        int i;
        i = search(e, &B){
            if(i != -1){
                B.value[i] = B.value[size];
            }
        }
    }
}
