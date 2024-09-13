#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define ElemType int

typedef struct Stack
{
    ElemType *array;
    int capacity;
    int top;
} Stack,*ArrayStack;

ArrayStack CreateStack(int capacity)
{
    ArrayStack stack;
    stack->array = (ElemType*)malloc(sizeof(ElemType) * capacity);
    if(stack->array == NULL) return NULL;
    stack->capacity = capacity;
    stack->top = -1;
    return stack;
}

bool push(ArrayStack stack,ElemType e)
{
    if(stack->top == stack->capacity - 1)
    { // 需要扩容
        int newCapacity = stack->capacity + (stack->capacity >> 1);
        ElemType *newArray = realloc(stack->array , newCapacity * sizeof(ElemType));
        if(newArray == NULL) return false;
        stack->array = newArray;
        stack->capacity = newCapacity;
    }
    stack->array[++stack->top] = e;
    return true;
}

bool is_empty(ArrayStack stack)
{
    return stack->top==-1;
}

ElemType pop(ArrayStack stack)
{
    return stack->array[stack->top--];
}

void PrintStack(ArrayStack stack)
{
    for(int i=0;i<=stack->top;++i)
    {
        printf("%d ",stack->array[i]);
    }
    printf("\n");
}

int main()
{
    ArrayStack stack = CreateStack(10);
    printf("%d\n",is_empty(stack));
    for(int i=0;i<3;++i)
    {
        push(stack,i+1);
    }
    printf("%d\n",pop(stack));
    PrintStack(stack);
    return 0;
}