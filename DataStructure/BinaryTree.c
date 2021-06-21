#include <stdio.h>
#include <stdlib.h>
typedef char Label;

typedef struct node_tag *Node;
typedef struct node_tag{
    Label label;
    Node left;
    Node right;
}NodeStruct;
typedef NodeStruct *BiTree;

BiTree Create(Label L){
    Node p;
    p = malloc(sizeof(NodeStruct));
    p->label = L;
    p->left = NULL;
    p->right = NULL;
    return (BiTree)p;
}

Node FindLeftChild(Node n){
    if(n==NULL){
        printf("FindLeftChild:Empty Node.\n");
        return NULL;
    }
    return n->left;
}

Node FindRightChild(Node n){
    if(n==NULL){
        printf("FindRightChild:Empty Node.\n");
        return NULL;
    }
    return n->right;
}

Node InsertLeftChild(Node n, Label L){
    Node p;
    if(n==NULL){
        printf("InsertLeftChild:Empty Node.\n");
        return NULL;
    }
    if(n->left==NULL){
        p = malloc(sizeof(NodeStruct));
        p->label = L;
        p->left = NULL;
        p->right = NULL;
        n->left =p;
        return p;
    }
    else return NULL;
}

Node InsertRightChild(Node n, Label L){
    Node p;
    if(n==NULL){
        printf("InsertRightChild:Empty Node.\n");
        return NULL;
    }
    if(n->right==NULL){
        p = malloc(sizeof(NodeStruct));
        p->label = L;
        p->right = NULL;
        p->left = NULL;
        n->right =p;
        return p;
    }
    else return NULL;
}

int DeleteLeftChild(Node n){
    Node c;
    if(n==NULL){
        printf("DeleteLeftChild:Empty Node.\n");
        return 0;
    }
    c = n->left;
    if(c==NULL) return 0;
    else if(c->left != NULL || c->right != NULL) return 0;
    else{
        n->left = NULL;
        free(c);
        return 1;
    }
}

int DeleteRightChild(Node n){
    Node c;
    if(n==NULL){
        printf("DeleteRightChild:Empty Node.\n");
        return 0;
    }
    c = n->right;
    if(c==NULL) return 0;
    else if(c->right != NULL || c->left != NULL) return 0;
    else{
        n->right = NULL;
        free(c);
        return 1;
    }
}

int DeleteSubtree(Node n){
    Node c,d;
    if(n==NULL) return 0;
    c = n->left;
    d = n->right;
    free(n);
    DeleteSubtree(c);
    DeleteSubtree(d);
    return 1;
}

int DeleteLeftSubtree(Node n){
    Node c;
    int i;
    if(n==NULL){
        printf("DeleteLeftSubtree:Empty Node.\n");
        return 0;
    }
    c = n->left;
    n->left = NULL;
    i = DeleteLeftSubtree(c);
    return i;
}

int DeleteRightSubtree(Node n){
    Node c;
    int i;
    if(n==NULL){
        printf("DeleteRightSubtree:Empty Node.\n");
        return 0;
    }
    c = n->right;
    n->right = NULL;
    i = DeleteRightSubtree(c);
    return i;
}

Node CopySubtree(Node s){
    Node d;
    if(s==NULL) return NULL;
    d = malloc(sizeof(NodeStruct));
    d->label = s->label;
    if(s->left==NULL) d->left = NULL;
    else d->left = CopySubtree(s->left);
    if(s->right==NULL) d->right = NULL;
    else d->right = CopySubtree(s->right);
    return d;
}

Node InsertLeftSubtree(Node n, BiTree T){
    if(n==NULL){
        printf("InsertLeftSubtree:Empty Node.\n");
        return NULL;
    }
    if(n->left!=NULL) return NULL;
    else{
        n->left = CopySubtree((Node)T);
        return n->left;
    }
}

Node InsertRightSubtree(Node n, BiTree T){
    if(n==NULL){
        printf("InsertRightSubtree:Empty Node.\n");
        return NULL;
    }
    if(n->right!=NULL) return NULL;
    else{
        n->right = CopySubtree((Node)T);
        return n->right;
    }
}

void printTree(Node n){
    if(n==NULL) return;
    printf("%c ",n->label);
    if(n->left!=NULL){
        printTree(n->left);
    }
    if(n->right!=NULL){
        printTree(n->right);
    }
    return;
}

int main(){
    Node p;
    BiTree T;
    T = Create('A');
    InsertLeftChild((Node)T,'B');
    InsertLeftChild((FindLeftChild((Node) T)),'C');
    InsertRightChild((FindLeftChild((Node) T)),'D');
    InsertRightChild((Node)T,'E');
    InsertRightChild((FindRightChild((Node)T)),'F');
    printTree((Node) T);
    return 0;
}
