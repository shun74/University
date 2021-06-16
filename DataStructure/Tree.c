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
        printf("Can't follow empty\n");
        return NULL;
    }
    if(n->tag) return NULL;
    else return n->next;
}

Node FindLeftmostChild(Node n){
    if(n==NULL){
        printf("Can't follow empty\n");
        return NULL;
    }
    if(n->child==NULL) return NULL;
    else return n->child;
}

Node InsertRightSibling(Node n, Label L){
    Node p;
    if(n==NULL){
        printf("Empty Node\n");
        return NULL;
    }
    p = malloc(sizeof(NodeStruct));
    p->label = L;
    if(!n->tag){
        p->next = n->next;
        p->tag = 0;
        p->child = NULL;
        n->next = p;
    } else {
        n->tag = 0;
        p->next = n->next;
        p->tag = 1;
        p->child = NULL;
        n->next = p;
    }
    return p;
}

Node InsertLeftmostChild(Node n, Label L){
    Node p;
    if(n==NULL) {
        printf("Empty Node\n");
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
        printf("Empty Node\n");
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
        printf("Empty Node\n");
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
        printf("Empty Node\n");
        return 0;
    }
    c = FindRightSibling(n);
    if(c == NULL) return 0;
    n->next = c->next;
    n->tag = c->tag;
    DeleteSubtree(c);
    return 1;
}


Label Retrive(Node n){
    if(n==NULL) {
        printf("Empty Node\n");
        return ' ';
    }
    return n->label;
}

int Update(Node n, Label l){
    if(n==NULL){
        printf("Empty Node\n");
        return 0;
    }
    n->label = l;
    return 1;
}

int EmptyNode(Node n){
    if(n==NULL) return 1;
    return 0;
}

void PreOrder(Node n){
    Node c;
    printf("%c ",Retrive(n));
    c = FindLeftmostChild(n);
    if(c==NULL) {
        return;
    }
    while(c!=NULL){
        PreOrder(c);
        c = FindRightSibling(c);
    }
    return;
}

void CopyTree(Node n1, Node n2, int first){
    // Use in Subtree Function
    if(first) Update(n1,Retrive(n2));
    Node c1,c2;
    c1 = n1;
    c2 = n2;
    if(c2==NULL) return;
    if(!c2->tag&&c2->child==NULL) return;
    if(c2->child!=NULL){
        c2 = FindLeftmostChild(c2);
        InsertLeftmostChild(c1,Retrive(c2));
        c1 = FindLeftmostChild(c1);
        CopyTree(c1,c2,0);
    }
    while(!c2->tag){
        c2 = FindRightSibling(c2);
        InsertRightSibling(c1,Retrive(c2));
        c1 = FindRightSibling(c1);
        CopyTree(c1,c2,0);
    }
    return;
}

void InsertRightSubtree(Node n1, Node n2){
    Tree tmp1 = Create('0');
    CopyTree(tmp1,n2,1);
    if(!n1->tag){
        tmp1->next = n1->next;
        tmp1->tag = 0;
        n1->next = tmp1;
    } else {
        tmp1->next = NULL;
        tmp1->tag = 1;
        n1->next = tmp1;
        n1->tag = 0;
    }
    return;
}

void InsertLeftmostSubtree(Node n1, Node n2){
    Tree tmp1 = Create('0');
    CopyTree(tmp1,n2,1);
    if(n1->child!=NULL){
        tmp1->next = n1->child;
        tmp1->tag = 0;
        n1->child = tmp1;
    } else {
        tmp1->next = NULL;
        tmp1->tag = 1;
        n1->child = tmp1;
    }
    return;
}

int main(){
    Tree T = Create('A');
    InsertLeftmostChild((Node)T, 'H');
    InsertLeftmostChild((Node)T, 'B');
    InsertRightSibling(FindLeftmostChild((Node)T), 'E');
    InsertLeftmostChild(FindLeftmostChild((Node)T), 'C');
    InsertRightSibling(FindLeftmostChild(FindLeftmostChild((Node)T)), 'D');
    InsertLeftmostChild(FindRightSibling(FindLeftmostChild((Node)T)), 'G');
    InsertLeftmostChild(FindRightSibling(FindLeftmostChild((Node)T)), 'F');
    PreOrder(T);
    printf("\n");

    // Subtree
    /* T1   a
           /
          b--insert--c  */
    Tree T1 = Create('a');
    InsertLeftmostChild((Node)T1, 'b');
    InsertRightSibling(FindLeftmostChild((Node)T1),'c');
    InsertRightSubtree(FindLeftmostChild((Node)T1),(Node)T);
    PreOrder(T1);
    printf("\n");
    /* T2   a
           /
        insert--b--c  */
    Tree T2 = Create('a');
    InsertLeftmostChild((Node)T2,'b');
    InsertRightSibling(FindLeftmostChild((Node)T2),'c');
    InsertLeftmostSubtree((Node)T2,(Node)T);
    PreOrder(T2);
}
