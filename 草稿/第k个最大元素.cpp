#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    int partition(vector<int>& nums, int low, int high) {
        int temp = nums[0];
        while(high > low)
        {
            while(high>low && nums[high]>temp) high--;
            nums[low]=nums[high];
            while(high>low && nums[low]<temp) low++;
            nums[high]=nums[low];
        }
        nums[high]=temp;
        return high;
    }

    int quick_sort(vector<int>& nums,int low,int high,int k)
    {
        int pivot = partition(nums,low,high);
        if(pivot == nums.size()-k) return nums[pivot];
        else if(pivot < nums.size()-k) return quick_sort(nums,pivot+1,high,k);
        else return quick_sort(nums,low,pivot-1,k);
    }

    int findKthLargest(vector<int>& nums, int k) {
        return quick_sort(nums,0,nums.size()-1,k);
    }
};