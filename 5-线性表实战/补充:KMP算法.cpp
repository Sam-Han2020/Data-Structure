// 补充: KMP算法
#include <iostream>
#include <vector>
using namespace std;

int n, m;
string p, s;

int main()
{
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(false);
    cin >> n >> p >> m >> s;
    string a = p + "#" + s;
    vector<int> pi(a.size());
    for (int i = 1; i < a.size(); ++i) // 1开始，重要！！！
    {
        int len = pi[i - 1]; // ✅ 修正初始化方式
        while (len && a[i] != a[len]) {
            len = pi[len - 1];
        }
        if (a[i] == a[len]) ++len;
        pi[i] = len;
        if (pi[i] == n) { // ✅ 当匹配到整个模式串时
            cout << i - 2 * n << " "; // ✅ 修正位置计算
        }
    }
    return 0;
}
