#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n,m;cin>>n>>m;
    vector<vector<long double>> p(n,vector<long double>(n,1.0));
    cir(i,0,m){
        int u,v;long double x;cin>>u>>v>>x;--u;--v;
        p[u][v]=p[v][u]=x;
    }
    vector<long double> f(1<<n);
    vector<int> vis(1<<n);
    auto dfs=[&](auto __self,int s){
        auto res=1.0l;
        if(vis[s]) return f[s];
        vis[s]=true;
        cir(x,0,(1<<n)) if(x!=s&&(x&s)==x&&((x&(-x))==(s&(-s)))){
            auto up=1.0l;
            cir(i,0,n) if((x>>i)&1) cir(j,0,n) if((((s^x)>>j)&1)) up*=p[i][j];
            res-=up*__self(__self,x);
        }
        return f[s]=res;
    };
    cout<<fixed<<setprecision(3)<<dfs(dfs,(1<<n)-1)<<'\n';
    return 0;
}
