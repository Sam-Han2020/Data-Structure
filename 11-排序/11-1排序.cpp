#include <iostream>
#include <queue>
using namespace std;

void bubbleSort(int arr[],int size) 
{
    for(int i=0;i<size-1;++i)
    {
        bool flag = true;
        for(int j=0;j<size-1-i;++j) // 最后面有i个是排好的
        {
            if(arr[j] > arr[j+1]) {
                swap(arr[j],arr[j+1]);
                flag = false;
            }
        }
        if(flag) break;
    }
}

void insertSort(int arr[],int size) 
{
    for(int i=1;i<size;++i)
    {
        int tmp = arr[i];
        int j;
        for(j=i-1;j>=0;--j)
        {
            if(arr[j] > tmp) {
                arr[j+1] = arr[j];
            } else {
                arr[j+1] = tmp; 
                break;
            }
        }
        if(j<0) {
            arr[0] = tmp;
        }
    }
}

void insertSort1(int arr[],int size) 
{
    for(int i=1;i<size;++i) {
        int tmp = arr[i],j=i;
        while(j>0 && arr[j-1]>tmp) {
            arr[j] = arr[j-1];
            --j;
        }
        arr[j] = tmp;
    }
}

void selectSort(int arr[],int size)
{
    for(int i=0;i<size-1;++i)
    {
        int min = i;
        for(int j=i;j<size;++j)
        {
            if(arr[j]<arr[min]) min = j;
        }
        swap(arr[i],arr[min]);
    }
}

void selectSort1(int arr[],int size)
{
    int left = 0 , right = size - 1;
    while(left < right)
    {
        int min = left , max = right;
        for(int i=left;i<=right;++i)
        {
            if(arr[i]<arr[min]) min = i;
            if(arr[i]>arr[max]) max = i;
        }
        swap(arr[max],arr[right]);
        if(min == right) min = max;
        swap(arr[min],arr[left]);
        ++left;
        --right;
    }
}

void quickSort(int arr[],int start,int end)
{
    if(start >= end) return;
    int left = start , right = end , pivot = arr[left];
    while(left < right)
    {
        while(left < right && arr[right] >= pivot) --right;
        arr[left] = arr[right];
        while(left < right && arr[left] <= pivot) ++left;
        arr[right] = arr[left];
    }
    arr[left] = pivot;
    quickSort(arr,start,left-1);
    quickSort(arr,left+1,end);
}

void dualPivotQuickSort(int arr[],int start,int end)
{
    if(start >= end) return;
    if(arr[start] > arr[end])
        swap(arr[start],arr[end]);
    int pivot1 = arr[start],pivot2 = arr[end];
    int left = start , right = end , mid = left + 1;
    while(mid < right)
    {
        if(arr[mid] < pivot1) swap(arr[++left],arr[mid++]);
        else if(arr[mid] <= pivot2) ++mid;
        else {
            while(arr[--right] >= pivot2 && right > mid);
            if(mid >= right) break;
            swap(arr[mid],arr[right]);
        }
    }
    swap(arr[start],arr[left]);
    swap(arr[end],arr[right]);
    dualPivotQuickSort(arr,start,left-1);
    dualPivotQuickSort(arr,left+1,right-1);
    dualPivotQuickSort(arr,right+1,end);
}

void shellSort(int arr[],int size)
{
    int delta = size / 2;
    while(delta >= 1)
    {
        for(int i=delta;i<size;++i)
        {
            int j = i, tmp = arr[i];
            while(j >= delta && arr[j - delta] > tmp)
            {
                arr[j] = arr[j - delta];
                j -= delta; // 选择排序的后移操作
            }
            arr[j] = tmp;
        }
        delta /= 2;
    }
}

void heapSort(int arr[],int size)
{
    priority_queue<int,vector<int>,greater<int>> pque;
    for(int i=0;i<size;++i) pque.push(arr[i]);
    for(int i=0;i<size;++i)
    {
        arr[i] = pque.top();
        pque.pop();
    }
}

void makeHeap(int *arr,int start,int end)
{ // 建立一个大根堆
    while(start*2+1 <= end) // 根结点的左孩子不超出
    {
        int child = start*2+1; // 根结点的左孩子
        if(child + 1 <= end && arr[child] < arr[child+1]) ++child; // 看情况取右孩子，取到了最大的孩子
        if(arr[child] > arr[start]) swap(arr[child],arr[start]); // 看情况交换
        start = child; // 下一个需要调整的对象
    }
}

void heapSort1(int arr[],int size)
{
    for(int i=size/2-1;i>=0;--i) // 从最后一个非叶子结点，到根结点，建立大根堆
        makeHeap(arr,i,size-1);
    for(int i=size-1;i>0;--i)
    {
        swap(arr[i],arr[0]); // 堆顶arr[0]就是最大的元素，把它搬到最后面
        makeHeap(arr,0,i-1); // 剩下的0~i-1重新建堆，由于只有堆顶不满足，只需要建立一次就行，保证arr[0]最大
    }
}

void merge(int arr[],int tmp[],int left,int leftEnd,int right,int rightEnd) // 两个数组合并为有序的
{
    int i = left,size = rightEnd-left+1;
    while(left<=leftEnd && right<=rightEnd)
    {
        if(arr[left] <= arr[right]) tmp[i++] = arr[left++];
        else tmp[i++] = arr[right++];
    }
    while(left<=leftEnd) tmp[i++] = arr[left++];
    while(right<=rightEnd) tmp[i++] = arr[right++];
    for(int j=0;j<size;++j,--rightEnd) arr[rightEnd] = tmp[rightEnd];
}

void mergeSort(int arr[],int tmp[],int start,int end)
{
    if(start>=end) return; // 递归退出条件
    int mid = (start+end) / 2; // 把数组分成两半，再归并排序
    mergeSort(arr,tmp,start,mid);
    mergeSort(arr,tmp,mid+1,end);
    merge(arr,tmp,start,mid,mid+1,end);
}

int main()
{
    int arr[] = {3,5,7,2,9,0,6,1,8,4};
    int size = sizeof(arr)/sizeof(int);
    // bubbleSort(arr,size);
    // insertSort1(arr,size);
    // selectSort(arr,size);
    // selectSort1(arr,size);
    // quickSort(arr,0,size-1);
    // dualPivotQuickSort(arr,0,size-1);
    // shellSort(arr,size);
    // heapSort(arr,size);
    // heapSort1(arr,size);
    int tmp[size];
    mergeSort(arr,tmp,0,size-1);
    for(int i=0;i<size;++i) 
        cout<<arr[i]<<" ";
    return 0;
}