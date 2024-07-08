#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
struct edge{int u,w;};
vector<vector<edge>> G;
vector<vector<int>> UP,MX;
vector<int> H;int HT;
const int _inf=1e9+7;
void dfs(int u,int w=0,int f=0){
    UP[u][0]=f;H[u]=H[f]+1;MX[u][0]=w;
    cir(i,1,HT+1){
        UP[u][i]=UP[UP[u][i-1]][i-1];
        MX[u][i]=max(MX[u][i-1],MX[UP[u][i-1]][i-1]);
    }
    for(auto&i:G[u]) if(i.u!=f) dfs(i.u,i.w,u);
}
int maxlca(int u,int v){
    int res=0;
    if(u==v) return res;
    if(H[u]<H[v]) swap(u,v);
    cir(i,0,HT) if((1<<i)&(H[u]-H[v]))
        res=max(res,MX[u][i]),u=UP[u][i];
    if(u==v) return res;
    for(int i=HT;~i;--i) if(UP[u][i]!=UP[v][i])
        res=max({res,MX[u][i],MX[v][i]}),
            u=UP[u][i],v=UP[v][i];
    return max({MX[u][0],MX[v][0],res});
}
template<typename T>
struct dsu{
    vector<T> F;
    dsu(T _n):F(_n){iota(F.begin(),F.end(),0);}
    int findset(T x){return F[x]==x?x:F[x]=findset(F[x]);}
    void merge(T u,T v){F[findset(u)]=findset(v);}
};
struct edge_t{int u,v,w,id;};
using lint=long long;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,m;cin>>n>>m;G.resize(n+1);
    HT=log2(n)+2;MX.assign(n+1,vector<int>(HT+1));
    UP.assign(n+1,vector<int>(HT+1));
    H.resize(n+1);dsu<int> ds(n+1);
    vector<edge_t> ve(m);
    int cnt=0;
    for(auto&i:ve) cin>>i.u>>i.v>>i.w,i.id=cnt++;
    auto vx=ve;
    sort(ve.begin(),ve.end(),
        [](edge_t&a,edge_t&b){return a.w<b.w;});
    lint cntx=0;vector<bool> ol(cnt);
    for(auto&i:ve){
        if(ds.findset(i.u)==ds.findset(i.v))
            continue;
        ds.merge(i.u,i.v);
        G[i.u].push_back({i.v,i.w});
        G[i.v].push_back({i.u,i.w});
        cntx+=i.w;ol[i.id]=true;
    }
    dfs(1);
    for(auto&i:vx){
        if(ol[i.id]){cout<<cntx<<'\n';continue;}
        cout<<cntx+i.w-maxlca(i.u,i.v)<<'\n';
    }
    return 0;
}
