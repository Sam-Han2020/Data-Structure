#include <iostream>
using namespace std;

/**
 * 
 * 根节点占据1个节点，剩下 n-1 个节点分配给左子树和右子树。
 * 若左子树有 j 个节点，右子树则有 n-1-j 个节点。
 */

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