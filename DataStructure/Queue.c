#include <stdio.h>
typedef int Element;
#define maxsize 100

typedef struct{
    int front, rear;
    Element value[maxsize];
} Queue;

void Create(Queue *Q){
    Q->front = 0;
    Q->rear = maxsize - 1;
}

int AddOne(int i){
    return (i+1) % maxsize;
}

int Empty(Queue *Q){
    return(AddOne(Q->rear) == Q->front);
}

int Retrieve(Queue *Q, Element *v){
    if(Empty(Q)) return 0;
    else{
        *v = Q->value[Q->front];
        return 1;
    }
}

int EnQueue(Queue *Q, Element e){
    if(AddOne(AddOne(Q->rear)) == Q->front) return 0;
    else {
        Q->rear = AddOne(Q->rear);
        Q->value[Q->rear] = e;
        return 1;
    }
}

int DeQueue(Queue *Q){
    if(Empty(Q)) return 0;
    else {
        Q->front = AddOne(Q->front);
        return 1;
    }
}

int main(){
    Queue q;
    Create(&q);

    printf("Empty? %d\n",Empty(&q));

    printf("EnQueue? %d\n",EnQueue(&q, 10));
    printf("EnQueue? %d\n",EnQueue(&q, 20));
    printf("EnQueue? %d\n",EnQueue(&q, 30));
    printf("Empty? %d\n",Empty(&q));

    Element a;

    printf("Retrieve? %d\n",Retrieve(&q, &a));
    printf("a=%d\n",a);
    printf("DeQueue? %d\n",DeQueue(&q));
    printf("Retrieve? %d\n",Retrieve(&q, &a));
    printf("a=%d\n",a);
    printf("DeQueue? %d\n",DeQueue(&q));
    printf("Retrieve? %d\n",Retrieve(&q, &a));
    printf("a=%d\n",a);
    printf("DeQueue? %d\n",DeQueue(&q));
    printf("Empty? %d\n",Empty(&q));
}
