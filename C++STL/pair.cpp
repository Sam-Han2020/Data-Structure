#include <iostream>
#include <utility>

using namespace std;

int main()
{
    pair<int,int> p1 = {1,2};
    pair<int,int> p2 = make_pair(1,2);
    cout<< p1.first << " " << p1.second << endl;
    if(p1==p2)
    {
        cout<<"yes"<<endl;
    }
    pair<char,int> cp = {'a',1};
    pair<pair<int,int>,int> p3;
    return 0;
}