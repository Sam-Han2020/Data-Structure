#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int,int> hashMap; // unordered_map的底层实现是哈希表
        vector<int> res(2,-1);
        for(int i=0;i<nums.size();++i) {
            if(hashMap.count(target - nums[i])) {
                res = {i,hashMap[target - nums[i]]};
                return res;
            } else {
                hashMap[nums[i]] = i; // 查找表，就是反过来记录，用哈希表实现
            }
        }
        return res;
    }
};
