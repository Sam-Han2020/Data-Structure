#include <iostream>
#include <vector>

using namespace std;

int main()
{
    // vector<vector<int>> dp(5,vector<int>(6,10)); // 初始化一个5行6列每个元素值为10数组
    // vector<vector<vector<int>>> dp2(5,vector<vector<int>>(6,vector<int>(4))); // int mat[5][6][4]
    vector<int> arr;
    arr.push_back(1);
    arr.push_back(2);
    arr.push_back(3);

    // arr.resize(5); // 长度是5，多出来的默认值为0
    // arr.resize(5,3); // 多出来的默认值为3
    // arr.resize(1) // 改短了直接删掉

    cout<<arr.size()<<endl;

    for(auto &ele:arr) cout<<ele<<endl;

    arr.pop_back();
    arr.pop_back();

    for(auto &ele:arr) cout<<ele<<endl;

    arr.clear();
    cout<<arr.size()<<endl;
    cout<<arr.empty()<<endl;

    return 0;
}