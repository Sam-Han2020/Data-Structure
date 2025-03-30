#include <iostream>
using namespace std;

#define E int

// 大根堆
typedef struct MaxHeap {
    E *arr;
    int size;
    int capacity;
} *Heap;

Heap CreateHeap(int capacity)
{
    Heap heap = new MaxHeap;
    heap->size = 0;
    heap->capacity = capacity;
    heap->arr = (E*)malloc(heap->capacity*sizeof(E));
    return heap;
}

bool insert(Heap heap, E element)
{
    if(heap->size == heap->capacity) return false;
    int index = ++heap->size; // 从1开始存
    while(index > 1 && element > heap->arr[index/2])
    { // 堆化过程
        heap->arr[index] = heap->arr[index / 2];
        index /= 2;
    }
    heap->arr[index] = element;
    return true;
}

E deleteNode(Heap heap) // 删除堆顶部的元素
{
    E max = heap->arr[1] , e = heap->arr[heap->size--];
    int index = 1;
    while(index*2 <= heap->size)
    {
        int child = index * 2; // 左孩子下标
        if(child < heap->size && heap->arr[child] < heap->arr[child+1])
            child += 1; // 视情况而定，切换到右孩子，保证是最大的孩子
        if(e >= heap->arr[child]) break; // 不需要调整的情况
        else heap->arr[index] = heap->arr[child]; // 需要换上去的情况
        index = child; // 更新index
    }
    heap->arr[index] = e; // 找到了把最后一个元素应当换上去的位置
    return max;
}

void printHeap(Heap heap)
{
    for(int i=1;i<=heap->size;++i)
        cout<<heap->arr[i]<<" ";
}

int main()
{
    Heap heap = CreateHeap(10);
    insert(heap, 5);
    insert(heap, 2);
    insert(heap, 3);
    insert(heap, 7);
    insert(heap, 6);
    insert(heap, 11);
    for(int i=0;i<6;++i)
        cout<<deleteNode(heap)<<" "; // 从大到小被删除
    // printHeap(heap);
    return 0;
}