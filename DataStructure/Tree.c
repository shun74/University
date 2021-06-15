#include <stdio.h>
#include <stdlib.h>

typedef char Label;
typedef struct node_tag *Node;

typedef struct node_tag {
    Node child;
    Label label;
    int tag;
    Node next;
} NodeStruct;

typedef NodeStruct *Tree;

Tree Create(Label L){
    Node p;
    p = malloc(sizeof(NodeStruct));
    p->label = L;
    p->child = NULL;
    p->next = NULL;
    p->tag = 1;
    return((Tree)p);
}

Node FindRightSibling(Node n){
    if(n==NULL) {
        printf("Can't follow empty");
        return NULL;
    }
    if(n->tag) return NULL;
    else return n->next;
}

Node FindLeftmostChild(Node n){
    if(n==NULL){
        printf("Can't follow empty");
        return NULL;
    }
    if(n->child==NULL) return NULL;
    else return n->child;
}

Node InsertRightSibling(Node n, Label L){
    Node p;
    if(n==NULL){
        printf("Empty Node");
        return 0;
    }
    p = malloc(sizeof(NodeStruct));
    p->label = L;
    if(n->next != NULL){
        p->next = n->next;
        p->tag = 0;
        p->child = NULL;
        n->next = p;
    } else {
        p->next = n;
        p->tag = 0;
        p->child = NULL;
        n->next = p;
    }
    return p;
}

Node InsertLeftmostChild(Node n, Label L){
    Node p;
    if(n==NULL) {
        printf("Empty Node");
        return NULL;
    }
    p = malloc(sizeof(NodeStruct));
    p->label = L;
    if(n->child != NULL){
        p->next = n->child;
        p->tag = 0;
        p->child = NULL;
        n->child = p;
    } else {
        p->next = n;
        p->tag = 1;
        p->child = NULL;
        n->child = p;
    }
    return p;
}

int DeleteLeftmostChild(Node n){
    Node p;
    if(n==NULL){
        printf("Empty Node");
        return 0;
    }
    p = n->child;
    if(p==NULL) return 0;
    else if(p->child != NULL) return 0;
    else if(p->tag) n->child = NULL;
    else n->child = p->next;
    free(p);
    return 1; 
}

int DeleteSubtree(Node n){
    Node c,d;
    if(n==NULL) return 0;
    c = n->child;
    while(c!=NULL){
        d = FindRightSibling(c);
        DeleteSubtree(c);
        c = d;
    }
    free(n);
    return 1;
}

int DeleteLeftmostSubtree(Node n){
    Node c,d;
    if(n==NULL){
        printf("Empty Node");
        return 0;
    }
    c = n->child;
    if(n==NULL) return 0;
    n->child = FindRightSibling(c);
    DeleteSubtree(c);
    return 1;
}

int DeleteRightSubtree(Node n){
    Node c, d;
    if(n == NULL){
        printf("Empty Node");
        return 0;
    }
    c = FindRightSibling(n);
    if(c == NULL) return 0;
    n->next = c->next;
    n->tag = c->tag;
    DeleteSubtree(c);
    return 1;
}