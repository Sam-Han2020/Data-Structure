#include <stdio.h>
#include <stdlib.h>

typedef int E;

typedef struct List {
    E *array;
    int capacity;
    int size;
} ArrayList;

_Bool initList(ArrayList * list,int capacity)
{
    list->capacity = capacity;
    list->array = (E*)malloc(sizeof(E) * list->capacity);
    if(list->array == NULL) return 0;
    list->size = 0;
    return 1;
}

// 我这里的index表示下标，而不是位序
_Bool insertList(ArrayList *list,E element,int index)
{
    if(list->size >= list->capacity)
    {
        list->capacity += 10;
        realloc(list->array,(list->capacity) * sizeof(E));
    }
    if(list->size < index || index < 0) return 0; // 可插入的范围：0 - size (包括)
    for(int i = list->size - 1; i >= index ; --i)
    {
        list->array[i+1] = list->array[i];
    }
    list->array[index] = element;
    ++list->size;
    return 1;
} // O(n)

_Bool delElement(ArrayList *list,int index)
{
    if(list->size==0) return 0;
    for(int i=index;i<list->size - 1;++i)
    {
        list->array[i] = list->array[i+1];
    }
    --list->size;
    return 1;
} // O(n)

int findElem(ArrayList *list,E element)
{
    for(int i=0;i<list->size;++i)
        if(list->array[i] == element)
            return i;
    return -1;
} // O(n)

void printList(ArrayList *list)
{
    for(int i=0;i<list->size;++i)
        printf("%d ",list->array[i]);
    printf("\n");
}

int sizeList(ArrayList *list)
{
    return list->size;
}

E* getElem(ArrayList *list,int index)
{
    if(index < 0 || index > list->size - 1) return NULL;
    return &list->array[index];
} // O(n)

void delList(ArrayList * list)
{
    list->capacity = 0;
    free(list->array);
}

int main()
{
    ArrayList list;
    if(initList(&list,10))
    {
        insertList(&list,1,0);
        insertList(&list,2,0);
        insertList(&list,3,0);
        delElement(&list,0);
        // for(int i = 0 ; i < 30 ; ++i) insertList(&list,i,0);
        printList(&list);
        printf("%d\n",*getElem(&list,0));
        printf("%d\n",findElem(&list,1));
    }else{
        printf("顺序表初始化失败！\n");
    }
}