#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

const int N = 210 , INF = 0x3f3f3f3f;

int n,m,q;
int d[N][N];

void floyd()
{
    for(int k=1;k<=n;++k)
        for(int i=1;i<=n;++i)
            for(int j=1;j<=n;++j)
                d[i][j] = min(d[i][j],d[i][k] + d[k][j]);
}

int main()
{
    cin.tie(0)->sync_with_stdio(false);
    cin>>n>>m>>q;
    for(int i=1;i<=n;++i)
        for(int j=1;j<=n;++j)
            if(i==j) d[i][j] = 0;
            else d[i][j] = INF;
    while(m--)
    {
        int a,b,c;
        cin>>a>>b>>c;
        d[a][b] = min(d[a][b],c);
    }
    floyd();
    while(q--)
    {
        int a,b;
        cin>>a>>b;
        if(d[a][b] > 0x3f3f3f3f >> 1) cout<<"impossible\n";
        else cout<<d[a][b]<<"\n";
    }
    return 0;
}