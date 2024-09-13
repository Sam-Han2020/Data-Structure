#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define ElemType int

typedef struct QNode {
    ElemType element;
    struct QNode *next;
}QNode , *Queue;

typedef struct LinkedQueue
{
    Queue front,rear;
} *LinkedQueue;

Queue CreateQueue()
{
    Queue head = (Queue)malloc(sizeof(QNode));
    head->next = NULL;
    return head;
}

LinkedQueue initLinkedQueue()
{
    LinkedQueue lq = (LinkedQueue)malloc(sizeof(struct LinkedQueue));
    lq->front = lq->rear = NULL;
    return lq;
}

bool is_empty(LinkedQueue lq)
{
    return lq->front == NULL && lq->rear == NULL;
}

bool EnQueue(LinkedQueue lq,ElemType e)
{
    Queue node = CreateQueue();
    if(node == NULL) return false;
    node->element = e;
    if(is_empty(lq)) lq->front = lq->rear = node;
    else
    {
        node->next = lq->rear->next;
        lq->rear->next = node;
        lq->rear = lq->rear->next;
    }
    return true;
}

ElemType DeQueue(LinkedQueue lq)
{
    if(is_empty(lq)) return -1;
    ElemType elem = lq->front->element;
    if(lq->front == lq->rear) lq->front = lq->rear = NULL; 
    else lq->front = lq->front->next;
    return elem;
}

void PrintQueue(LinkedQueue lq)
{
    Queue q = lq->front;
    while(q)
    {
        printf("%d ",q->element);
        q = q->next;
    }
    printf("\n");
}

int main()
{
    LinkedQueue lq = initLinkedQueue();
    EnQueue(lq,1);
    EnQueue(lq,2);
    EnQueue(lq,3);
    EnQueue(lq,4);
    printf("%d\n",DeQueue(lq));
    printf("%d\n",DeQueue(lq));
    PrintQueue(lq);
    return 0;
}
