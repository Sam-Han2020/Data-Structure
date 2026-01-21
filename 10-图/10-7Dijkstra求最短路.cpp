// https://www.luogu.com.cn/problem/P4779

#include <bits/stdc++.h>
using namespace std;

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    using pii = pair<int,int>; // distance, u
    int n,m,s;
    cin >> n >> m >> s;
    auto graph = vector(n+1,vector<pii>()); // 邻接表
    while(m--) {
        int u,v,c; // 有向边
        cin >> u >> v >> c;
        graph[u].emplace_back(v,c);
    }
    priority_queue<pii,vector<pii>,greater<pii>> q;
    auto min_dist = vector(n+1,INT_MAX);
    auto calced = vector(n+1,0);
    min_dist[s] = 0;
    q.emplace(min_dist[s],s); // 距离一定放第一位
    while(q.size())
    {
        auto [dist,u] = q.top();
        q.pop();
        if(calced[u]) continue;
        calced[u] = true;
        for(auto [v,c]:graph[u])
        {
            if(min_dist[v] <= min_dist[u] + c) continue;
            min_dist[v] = min_dist[u] + c;
            q.emplace(min_dist[v], v);
        }
    }
    for(int i = 1; i <= n; ++i)
        cout << min_dist[i] << " ";
    return 0;
}
