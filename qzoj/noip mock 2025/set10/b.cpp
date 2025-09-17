#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n,m,q;cin>>n>>m>>q;
    vector<vector<pair<int,int>>> vx(n);
    cir(i,0,m){
        int u,v,w;cin>>u>>v>>w;--u;--v;
        vx[u].emplace_back(v,w);
        vx[v].emplace_back(u,w);
    }
    vector<int> vis(n),anc(n),val(n);
    vector<uint64_t> dis(n);
    auto dfs=[&](auto __self,int u,int c,uint64_t x){
        if(vis[u]) return 0;
        vis[u]=true;
        dis[u]=x;
        anc[u]=c;
        auto res=0;
        for(auto&[v,w]:vx[u]) if(vis[v]){
            res=__gcd((uint64_t)(res),w+dis[u]+dis[v]);
        }else{
            res=__gcd(res,__self(__self,v,c,x+w));
        }
        return res;
    };
    cir(i,0,n) if(!vis[i]) val[i]=dfs(dfs,i,i,0);
    cir(i,0,q){
        int u,v,k;cin>>u>>v>>k;--u;--v;
        if(anc[u]!=anc[v]){
            cout<<"NIE"<<'\n';
        }else if(u!=v){
            const auto g=(val[anc[u]]?__gcd(k,val[anc[u]]):k);
            cout<<(dis[u]+dis[v])%g<<'\n';
        }else{
            cout<<0<<'\n';
        }
    }
    return 0;
}
