#include <iostream>
#include <queue>

using namespace std;



int main()
{
    // 优先级队列，又名：堆
    // priority_queue<int> pque; // 大根堆
    // pque.push(1);
    // cout << pque.top() << endl; // 1
    // pque.push(3);
    // cout << pque.top() << endl; // 3
    // pque.push(2);
    // cout << pque.top() << endl; // 3
    // pque.push(4);
    // cout << pque.top() << endl; // 4
    // pque.pop();
    // cout << pque.top() << endl; // 3
    // pque.pop();
    // cout << pque.top() << endl; // 2
    // pque.pop();
    // cout << pque.top() << endl; // 1

    priority_queue<int,vector<int>,greater<int>> pque1; // 小根堆
    pque1.push(1);
    cout << pque1.top() << endl; // 1
    pque1.push(3);
    cout << pque1.top() << endl; // 1
    pque1.push(2);
    cout << pque1.top() << endl; // 1
    pque1.push(4);
    cout << pque1.top() << endl; // 1
    pque1.pop();
    cout << pque1.top() << endl; // 2
    pque1.pop();
    cout << pque1.top() << endl; // 3
    pque1.pop();
    cout << pque1.top() << endl; // 4

    // priority_queue 所有元素不可修改
    // 以下方法修改堆顶元素
    int x = pque1.top();
    pque1.pop();
    pque1.push(x-1);
    cout << pque1.top() << endl; // 3
    return 0;
}