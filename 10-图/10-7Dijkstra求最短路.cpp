#include <iostream>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;

typedef pair<int,int> PII;

const int N = 150010;

int n,m;
int h[N],w[N],e[N],ne[N],idx; // 稀疏图，采用邻接表
int d[N];
bool st[N];
priority_queue<PII,vector<PII>,greater<PII>> heap;

void add(int a,int b,int c)
{
    e[idx] = b;
    w[idx] = c;
    ne[idx] = h[a];
    h[a] = idx++;
}

int dijkstra()
{
    memset(d,0x3f,sizeof d);
    d[1] = 0;
    heap.push({0,1});
    while(heap.size())
    {
        auto t = heap.top();
        heap.pop();
        int ver = t.second , dist = t.first; // ver -> vertex
        if(ver == n) break;
        if(st[ver]) continue; 
        st[ver] = true;
        for(int i=h[ver];i!=-1;i=ne[i])
        {
            int j = e[i];
            /*
            一旦我们找到了从起点到某个点 j 的更短路径，
            就需要重新评估 j 对其它点的影响，
            所以才要把它“重新加入优先队列”，让它成为下一个可能扩展的点。
            */
            if(st[j]) continue;
            if(d[j]>dist+w[i])
            {
                d[j] = dist + w[i];
                heap.push({d[j],j});
            }
        }
    }
    if(d[n] > 0x3f3f3f3f >> 1) return -1;
    return d[n];
}

int main()
{
    cin.tie(0)->sync_with_stdio(false);
    cin>>n>>m;
    memset(h,-1,sizeof h); // h全部初始化为0xffffffff -> -1
    while(m--)
    {
        int a,b,c;
        cin>>a>>b>>c;
        add(a,b,c);
    }
    cout<<dijkstra()<<endl;
    return 0;
}