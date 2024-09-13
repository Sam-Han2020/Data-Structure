#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define ElemType int

typedef struct Queue
{
    ElemType *array;
    int capacity;
    int front,rear; // rear指向最后一个元素的下一个位置
} *ArrayQueue;

ArrayQueue CreateQueue(int capacity)
{
    ArrayQueue queue;
    queue->array = (ElemType*)malloc(sizeof(ElemType)*capacity);
    queue->capacity = capacity;
    queue->front = queue->rear = 0;
    return queue;
}

bool is_full(ArrayQueue queue)
{
    return (queue->rear +1) % (queue->capacity) == queue->front;
}

bool is_empty(ArrayQueue queue)
{
    return queue->rear == queue->front;
}

bool EnQueue(ArrayQueue queue,ElemType e)
{
    if(is_full(queue)) return false;
    queue->array[queue->rear] = e;
    queue->rear = (queue->rear +1) % (queue->capacity);
    return true;
}

ElemType DeQueue(ArrayQueue queue)
{
    if(is_empty(queue)) return -1;
    ElemType elem = queue->array[queue->front];
    queue->front = (queue->front + 1) % (queue->capacity);
    return elem;
}

void PrintQueue(ArrayQueue queue)
{
    int pos = queue->front;
    while((pos+1)%(queue->capacity) != queue->rear)
    {
        printf("%d ",queue->array[pos]);
        pos = (pos+1)%(queue->capacity);
    }
    printf("%d ",queue->array[pos]);
    printf("\n");
}

int main()
{
    ArrayQueue queue = CreateQueue(10);
    EnQueue(queue,1);
    EnQueue(queue,2);
    EnQueue(queue,3);
    EnQueue(queue,4);
    printf("%d\n",DeQueue(queue));
    printf("%d\n",DeQueue(queue));
    printf("%d\n",DeQueue(queue));
    printf("%d\n",DeQueue(queue));
    EnQueue(queue,1);
    EnQueue(queue,2);
    EnQueue(queue,3);
    EnQueue(queue,4);
    printf("%d\n",DeQueue(queue));
    printf("%d\n",DeQueue(queue));
    printf("%d\n",DeQueue(queue));
    printf("%d\n",DeQueue(queue));
    EnQueue(queue,1);
    EnQueue(queue,2);
    EnQueue(queue,3);
    EnQueue(queue,4);
    PrintQueue(queue);
    return 0;
}