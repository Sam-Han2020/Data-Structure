#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector<int> findDisappearedNumbers(vector<int>& nums) {
    int n = nums.size();
    vector<int> result;
    sort(nums.begin(),nums.end());
    nums.erase(unique(nums.begin(),nums.end()),nums.end());
    // for(int i=0;i<nums.size();++i)
    // {
    //     cout<<nums[i]<<" ";
    // }
    int pos=0;
    int num=1;
    while(pos<nums.size() and num<=n)
    {
        if(num<nums[pos])
        {
            result.push_back(num);
            ++num;
        }
        else
        {
            ++pos;
        }
    }
    
    for(int i=nums.back();i<=n;++i)
    {
        result.push_back(i);
    }
    return result;
}

int main()
{
    vector<int> nums = {4,3,2,7,8,2,3,1};
    vector<int> result = findDisappearedNumbers(nums);
    for(int i=0;i<result.size();++i)
    {
        cout<<result[i]<<" ";
    }
    return 0;
}