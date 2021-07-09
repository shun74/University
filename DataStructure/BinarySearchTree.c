#include <stdio.h>
#include <stdlib.h>
typedef int Element;

typedef struct node_tag *NodePointer;
typedef struct node_tag{
    Element label;
    NodePointer left, right;
} Node;
typedef NodePointer BSTree;

BSTree CreateTree(){
    BSTree T;
    T = malloc(sizeof(BSTree));
    T = NULL;
    return T;
}

void Insert(Element x, BSTree *t){
    if((*t)==NULL){
        *t = malloc(sizeof(Node));
        (*t)->left = NULL;
        (*t)->right = NULL;
        (*t)->label = x;
    }
    else if(x < (*t)->label) {
        Insert(x, &(*t)->left);
    }
    else if(x > (*t)->label) Insert(x, &(*t)->right);
    return;
}

Element DeleteMin(BSTree *t){
    Element y; NodePointer p;
    if((*t) == NULL) printf("Fatal Error");
    else if((*t)->left == NULL){
        y = (*t)->label; p = (NodePointer)(*t); free(p);
        (*t) = (*t)->right; return y;
    }
    else {
        y = DeleteMin(&((*t)->left));
        return y;
    }
}

void Delete(Element x, BSTree *t){
    NodePointer p;
    if((*t)==NULL) return;
    if(x < (*t)->label) Delete(x, &(*t)->left);
    else if(x > (*t)->label) Delete(x, &(*t)->right);
    else if((*t)->right==NULL){
        p = (NodePointer)(*t);
        (*t) = (*t)->right;
        free(p);
    }
    else if((*t)->left==NULL){
        p = (NodePointer)(*t);
        (*t) = (*t)->left;
        free(p);
    }
    else{
        (*t)->label = DeleteMin(&((*t)->right));
    }
    return;
}


void printTree(BSTree *t){
    if((*t)==NULL) return;
    if((*t)->left!=NULL) printTree(&((*t)->left));
    printf("%d ",(*t)->label);
    if((*t)->right!=NULL) printTree(&((*t)->right));
    return;
}

int main(){
    //演習の順番で二分探索木に要素を代入
    //printTreeは通りがけ順に要素を表示する関数
    BSTree T;
    T = CreateTree();
    Insert(7,&T);
    Insert(2,&T);
    Insert(10,&T);
    Insert(1,&T);
    Insert(4,&T);
    Insert(8,&T);
    Insert(11,&T);
    Insert(3,&T);
    Insert(6,&T);
    Insert(9,&T);
    Insert(12,&T);
    Insert(5,&T);
    printTree(&T);
}
