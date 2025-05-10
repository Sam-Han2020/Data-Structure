#include <iostream>
#include <stack>
#include <vector>

using namespace std;

int main()
{
    stack<double> stk;
    stk.push(1.0);
    stk.push(1.4);
    cout<<stk.size()<<endl;
    cout<<stk.top()<<endl;
    stk.pop();
    cout<<stk.top()<<endl;
    stk.pop();
    cout<<stk.empty()<<endl;

    // vector模拟栈
    vector<double> vec;
    vec.push_back(1.0);
    vec.push_back(1.4);
    cout<<vec.back()<<endl;
    vec.pop_back();
    cout<<vec.back()<<endl;
    return 0;
}