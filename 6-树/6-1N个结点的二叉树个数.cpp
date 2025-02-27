#include <iostream>
using namespace std;

int main()
{
    int n;
    cin >> n;
    if (n < 2)
    {
        cout << 1 << endl;
        return 0;
    }
    int h[n + 1] = {0}; // 一定要初始化为0
    h[0] = h[1] = 1;    // 采用动态规划
    for (int i = 2; i <= n; ++i)
    {
        for (int j = 0; j < i; ++j)
            h[i] += h[j] * h[i - 1 - j];
    }
    cout << h[n] << endl; // 卡特兰数
    return 0;
}