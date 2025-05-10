#include <iostream>
#include <set>

using namespace std;

int main()
{
    set<int> st;
    st.insert(1);
    st.insert(2);
    st.insert(2);
    st.insert(0);
    st.erase(2);
    if(st.find(1) != st.end()) // 查找，找不到返回伪迭代器st.end()
    {
        cout<<"yes"<<endl;
    }
    if(st.count(1)) // 同样是查找 ，集合具有互异性，只能返回0或者1
    {
        cout<<"yes"<<endl;
    }
    if(st.count(2))
    {
        cout<<"yes"<<endl;
    }
    for(auto &ele:st)
        cout<<ele<<endl;
    for(set<int>::iterator it = st.begin();it!=st.end();++it)
        cout<<*it<<endl;
    cout<<*st.begin()<<endl;
    st.clear();
    cout<<st.empty()<<endl;
    return 0;
}