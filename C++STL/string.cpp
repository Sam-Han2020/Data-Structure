#include <iostream>
using namespace std;

int main()
{
    // string s; // 不能用scanf读入
    // cin>>s;
    // string s(100,'0');
    string s;
    s = "awa";
    s[0] = 'b';
    cout<<s<<endl;
    string s1 = "123",s2 = "123";
    if(s1==s2) cout<<"yes"<<endl;
    cout<<s1+s2<<endl;
    s1 = "123123123123";
    cout<<s1.substr(3,4)<<endl; //"1231"
    if(s1.find("3124 ")!=string::npos) cout<<"yes"<<endl;
    return 0;
}