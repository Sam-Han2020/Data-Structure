#include <iostream>
#include <cstring>

using namespace std;

const int N = 510 , INF = 0x3f3f3f3f;

int n,m;
int g[N][N];
int d[N];
bool st[N];

int prim()
{
    memset(d,0x3f,sizeof d);
    int res = 0; // 最小生成树里面，所有边长度之和
    for(int i=0;i<n;++i)
    {
        int t = -1; // 集合外到集合距离最短的点
        for(int j=1;j<=n;++j)
            if(!st[j] && (t==-1 || d[t] > d[j])) // 注意是大于
                t = j;
        
        if(i && d[t] == INF) return INF; // 重要
        if(i) res += d[t];
        for(int j=1;j<=n;++j) d[j] = min(d[j],g[t][j]);        
        st[t] = true;
    }
    return res;
}

int main()
{
    cin.tie(0)->sync_with_stdio(false);
    cin>>n>>m;
    memset(g,0x3f,sizeof g);
    while(m--)
    {
        int a,b,c;
        cin>>a>>b>>c;
        g[a][b] = g[b][a] = min(g[a][b],c);
    }
    int t = prim();
    if(t > INF >> 1) cout<<"impossible\n";
    else cout<<t<<"\n";
    return 0;
}