#include <stdio.h>
#include <stdlib.h>
typedef char Label;

typedef struct node_tag *Node;
typedef struct node_tag{
    Label label;
    Node left;
    Node right;
    int ltag;
    int rtag;
}NodeStruct;
typedef NodeStruct *BiTree;

BiTree Create(Label L){
    Node header,p;
    header = malloc(sizeof(NodeStruct));
    p = malloc(sizeof(NodeStruct));
    p->label = L;
    p->left = header;
    p->right = header;
    p->ltag = 0;
    p->rtag = 0;
    header->label = ' ';
    header->left = p;
    header->right = p;
    header->ltag = 1;
    header->rtag = 1;
    return (BiTree)header;
}

Node FindLeftChild(Node n){
    if(n->ltag) return n->left;
    else return NULL;
}

Node FindRightChild(Node n){
    if(n->rtag) return n->right;
    else return NULL;
}

Node InsertLeftChild(Node n, Label L){
    Node p;
    if(n==NULL) return 0;
    if(!n->ltag){
        p = malloc(sizeof(NodeStruct));
        p->label = L;
        p->left = n->left;
        p->right = n;
        p->ltag = 0;
        p->rtag = 0;
        n->left = p;
        n->ltag = 1;
        return p;
    }
    else return NULL;
}

Node InsertRightChild(Node n, Label L){
    Node p;
    if(n==NULL) return 0;
    if(!n->rtag){
        p = malloc(sizeof(NodeStruct));
        p->label = L;
        p->right = n->right;
        p->left = n;
        p->ltag = 0;
        p->rtag = 0;
        n->right = p;
        n->rtag = 1;
        return p;
    }
    else return NULL;
}

int DeleteLeftChild(Node n){
    Node c;
    if(n==NULL) return 0;
    if(!n->ltag) return 0;
    c = n->left;
    if(c->ltag) return 0;
    else {
        n->left = c->left;
        n->ltag = 0;
        free(c);
        return 1;
    }
}

int DeleteRightChild(Node n){
    Node c;
    if(n==NULL) return 0;
    if(!n->rtag) return 0;
    c = n->right;
    if(c->rtag) return 0;
    else {
        n->right = c->right;
        n->rtag = 0;
        free(c);
        return 1;
    }
}

int DeleteSubtree(Node n){
    Node c,d;
    if(n==NULL) return 0;
    c = n->left;
    d = n->right;
    if(n->ltag) DeleteSubtree(c);
    if(n->rtag) DeleteSubtree(d);
    free(n);
    return 1;
}

int DeleteLeftSubtree(Node n){
    Node p,c;
    if(n==NULL) return 0;
    c = n->left;
    p = n->left;
    while(p->ltag){
        p = p->left;
    }
    n->ltag = 0;
    n->left = p->left;
    DeleteSubtree(c);
    return 1;
}

int DeleteRightSubtree(Node n){
    Node p,c;
    if(n==NULL) return 0;
    c = n->right;
    p = n->right;
    while(p->rtag){
        p = p->right;
    }
    n->rtag = 0;
    n->right = p->right;
    DeleteSubtree(c);
    return 1;
}

Node FindInOrder(Node n, BiTree T){
    Node p;
    if(n==NULL) return NULL;
    p = n->right;
    if(n->rtag) while(p->ltag) p = p->left;
    else if(p==(Node)T) p = NULL;
    else return(p);
    return(p);
}

void printTree(Node n, BiTree T){
    if(n==NULL) return;
    if(n->label!=' ') printf("%c ",n->label);
    printTree(FindInOrder(n,T), T);
    return;
}

int main(){
    // CopySubTreeとInsetSubtreeは実装できませんでした.
    Node p;
    BiTree T;
    /*     +
         /   \
        *     ÷
       / \   / \
      1   2 6   3   */
    T = Create('+');
    InsertLeftChild(FindLeftChild((Node)T),'*');
    InsertLeftChild((FindLeftChild(FindLeftChild((Node)T))),'1');
    InsertRightChild((FindLeftChild(FindLeftChild((Node)T))),'2');
    InsertRightChild(FindLeftChild((Node)T),'/');
    InsertLeftChild((FindRightChild(FindLeftChild((Node)T))),'6');
    InsertRightChild((FindRightChild(FindLeftChild((Node)T))),'3');
    p = FindRightChild(FindLeftChild(FindLeftChild((Node)T)));
    printTree((Node)T, T);
    return 0;
}
