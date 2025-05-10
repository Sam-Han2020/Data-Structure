#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

bool cmp(pair<int,int> a,pair<int,int> b)
{
    // 不要带等号，否则容易runtime error
    // 第二位从小到大排序
    if(a.second!=b.second) 
        return a.second < b.second;
    // 第二位相同，第一位从大到小
    return a.first > b.first;
}

int main()
{
    // int a=1,b=2;
    // cout<<a<<" "<<b<<endl;
    // swap(a,b);
    // cout<<a<<" "<<b<<endl;
    // vector<int> arr{1,9,1,9,8,1,0};
    // // sort(arr.begin(),arr.end()); // 从小到大
    // // sort(arr.begin(),arr.end(),greater<int>()); // 从大到小
    // for(int i=0;i<arr.size();++i)
    //     cout<<arr[i]<<" ";
    // cout<<endl;
    // vector<pair<int,int>> parr{{1,9},{2,9},{8,1},{0,0}};
    // sort(parr.begin(),parr.end(),cmp);
    // for(auto ele:parr)
    //     cout<<ele.first<<" "<<ele.second<<endl;
    
    vector<int> arr1{0,1,1,1,8,9,9};
    int pos = lower_bound(arr1.begin(),arr1.end(),8) - arr1.begin(); // 大于等于8的第一个位置
    cout<< pos << endl; // 4
    pos = upper_bound(arr1.begin(),arr1.end(),8) - arr1.begin(); // 大于8的第一个位置
    cout<< pos << endl; // 5
    // 从第三个数开始找到结尾
    pos = upper_bound(arr1.begin()+2,arr1.end(),0) - arr1.begin();
    cout<< pos << endl; // 2
    pos = upper_bound(arr1.begin()+2,arr1.end(),999) - arr1.begin();
    if(pos == arr1.size())
    {
        cout<<"no"<<endl;
    }
    reverse(arr1.begin()+2,arr1.begin()+5); // 左闭右开
    for(auto ele:arr1)
        cout<<ele<<" ";
    cout<<endl;
    cout<<max(1,2)<<endl;
    cout<<max({1,2,3})<<endl; // C++ 11
    arr1 = {1,2,1,4,5,4,4};
    sort(arr1.begin(),arr1.end());
    // for(auto ele:arr1)
    //     cout<<ele<<" ";
    // cout<<endl;
    arr1.erase(unique(arr1.begin(),arr1.end()),arr1.end()); // unique函数作用是排序后删除相邻位置的元素，返回末尾迭代器位置，使用erase删除无效数据完成去重
    for(auto ele:arr1)
        cout<<ele<<" ";
    cout<<endl;
    return 0;
}