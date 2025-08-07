#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
static constexpr auto _inf=(int)(1e9+7);
class graph{
private:
    vector<vector<pair<int,int>>> gr;
    public:
    auto link(int u,int v,int w){
        gr[u].emplace_back(v,w);
        gr[v].emplace_back(u,w);
    }
    auto sp(int s){
        const auto n=(int)(gr.size());
        vector<int> vis(n),dis(n,_inf);
        dis[s]=0;
        while(true){
            auto x=make_pair(_inf,-1);
            cir(i,0,(int)(gr.size())) if(!vis[i]) x=min(x,{dis[i],i});
            if(x.second<0) break;
            const auto[w,u]=x;
            vis[u]=true;
            for(auto&[v,vw]:gr[u]) if(dis[v]>w+vw) dis[v]=w+vw;
        }
        return dis;
    }
    graph(int _n):gr(_n){}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n,m,v,e;cin>>n>>m>>v>>e;
    vector<int> c(n),d(n);
    vector<double> k(n);
    for(auto&i:c) cin>>i;
    for(auto&i:d) cin>>i;
    for(auto&i:k) cin>>i;
    graph gr(v+1);
    cir(i,0,e){
        int u,v,w;cin>>u>>v>>w;
        gr.link(u,v,w);
    }
    vector<vector<int>> sp(v+1);
    cir(i,1,v+1) sp[i]=gr.sp(i);
    vector<vector<array<double,2>>> f(n,vector<array<double,2>>(m+1));
    vector<vector<array<int,2>>> vis(n,vector<array<int,2>>(m+1));
    auto dfs=[&](auto __self,int u,int op,int w){
        if(w>m) return 1e18;
        if(u==n-1) return 0.0;
        if(vis[u][w][op]) return f[u][w][op];
        vis[u][w][op]=true;
        if(!op){
            return f[u][w][op]=min(
                __self(__self,u+1,0,w)+sp[c[u]][c[u+1]],
                (1-k[u+1])*(__self(__self,u+1,1,w+1)+sp[c[u]][c[u+1]])+
                k[u+1]*(__self(__self,u+1,1,w+1)+sp[c[u]][d[u+1]])
            );
        }else{
            return f[u][w][op]=min(
                __self(__self,u+1,0,w)+sp[c[u]][c[u+1]]*(1-k[u])+sp[d[u]][c[u+1]]*k[u],
                (1-k[u+1])*(__self(__self,u+1,1,w+1)+sp[c[u]][c[u+1]]*(1-k[u])+sp[d[u]][c[u+1]]*k[u])+
                k[u+1]*(__self(__self,u+1,1,w+1)+sp[c[u]][d[u+1]]*(1-k[u])+sp[d[u]][d[u+1]]*k[u])
            );
        }
    };
    const auto fx=dfs(dfs,0,0,0);
    const auto gx=dfs(dfs,0,1,1);
    cout<<fixed<<setprecision(2)<<min(fx,gx)<<'\n';
    return 0;
}
