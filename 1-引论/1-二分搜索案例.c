#include <stdio.h>

int binarySearch(int *nums,int target,int left,int right) // left和right是你要去寻找的范围的左右边界
{
    if(left > right) return -1;
    int mid = (left + right) / 2;
    if(nums[mid] == target) return mid;
    if(nums[mid] < target) return binarySearch(nums,target,mid+1,right);
    if(nums[mid] > target) return binarySearch(nums,target,left,mid-1);
}

int search(int *nums, int numsSize, int target)
{
    return binarySearch(nums,target,0,numsSize-1);
}

int main()
{
    int nums[] = {-1,0,3,5,9,12};
    int target = 9;
    printf("%d\n",search(nums,sizeof(nums)/sizeof(int),target));
    return 0;
}