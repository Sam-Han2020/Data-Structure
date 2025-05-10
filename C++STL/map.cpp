#include <iostream>
#include <map>
#include <vector>

using namespace std;

int main()
{
    map<int,int> mp;
    mp[2] = 1;
    mp[1] = 3;
    mp[0] = 4;
    mp[99999] = 66666;
    for(map<int,int>::iterator it = mp.begin();it != mp.end();++it)
    {
        cout<< it->first << " " << it->second << endl;
    }
    for(auto &pr:mp)
    {
        cout<<pr.first<<" "<<pr.second<<endl;
    }
    mp.erase(2);
    if(mp.find(0) != mp.end())
    {
        cout<<"yes"<<endl;
    }
    else
    {
        cout<<"no"<<endl;
    }
    cout<< mp[2] << endl; // 若不存在，赋初值是0
    cout<< mp.count(2) <<endl;
    cout<< mp.size() <<endl;
    mp.clear();
    cout<< mp.empty() << endl;

    map<string,int> smp;
    vector<string> word;
    word.push_back("awa");
    word.push_back("awa");
    word.push_back("awa");
    word.push_back("awa");
    word.push_back("bwb");
    word.push_back("bwb");

    for(int i=0;i<word.size();++i)
    {
        ++smp[word[i]];
    }

    for(auto &pr:smp)
    {
        cout<<pr.first<<" "<<pr.second<<endl;
    }

    map<int,int> tmp;
    tmp[0];
    cout<<tmp.count(0)<<endl; // 1

    // map不能用迭代器计算下标
    return 0;
}