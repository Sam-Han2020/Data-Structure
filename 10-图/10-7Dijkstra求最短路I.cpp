#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 510;

int n,m;
int g[N][N]; // 稠密图，用邻接矩阵
int dist[N];
bool st[N];

int dijkstra()
{
    memset(dist,0x3f,sizeof dist);
    dist[1] = 0;
    for(int i=0;i<n;++i)
    {
        int t=-1;
        for(int j=1;j<=n;++j)
            if(!st[j] && (t==-1 || dist[t]>dist[j]))
                t = j; // 找当前没有确定最短路的点中，长度最小那一个
        st[t] = true;
        for(int j=1;j<=n;++j)
            dist[j] = min(dist[j],dist[t]+g[t][j]);
    }
    if(dist[n] == 0x3f3f3f3f) return -1;
    return dist[n];
}

int main()
{
    cin>>n>>m;
    memset(g,0x3f,sizeof g); // g全部初始化为0x3f3f3f3f
    while(m--)
    {
        int a,b,c;
        cin>>a>>b>>c;
        g[a][b] = min(g[a][b],c); // 重边的情况，选取最小的一个
    }
    int t = dijkstra();
    cout<<t<<endl;
    return 0;
}