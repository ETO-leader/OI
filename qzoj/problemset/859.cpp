#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
static constexpr auto _inf=(int)(1e9+7);
class dsu{
private:
    vector<int> f;
public:
    auto findset(int u)->int{
        return f[u]==u?u:f[u]=findset(f[u]);
    }
    auto merge(int u,int v){
        f[findset(u)]=findset(v);
    }
    dsu(int _n):f(_n){iota(f.begin(),f.end(),0);}
};
class tree{
private:
    vector<vector<pair<int,int>>> gr;
    vector<vector<int>> up,upw;
    vector<int> h;
    static constexpr auto ups=21;
    auto dfs(int u,int f=0,int fw=-_inf)->void{
        up[0][u]=f;upw[0][u]=fw;
        h[u]=h[f]+1;
        cir(i,1,ups){
            up[i][u]=up[i-1][up[i-1][u]];
            upw[i][u]=max(upw[i-1][u],upw[i-1][up[i-1][u]]);
        }
        for(auto&[v,w]:gr[u]) if(v!=f) dfs(v,u,w);
    }
public:
    auto link(int u,int v,int w){
        gr[u].emplace_back(v,w);
        gr[v].emplace_back(u,w);
    }
    auto init(int r){dfs(r);}
    auto path(int u,int v){
        if(h[u]<h[v]) swap(u,v);
        auto res=-_inf;
        cir(i,0,ups) if((h[u]-h[v])&(1<<i)) res=max(res,upw[i][u]),u=up[i][u];
        if(u==v) return res;
        for(auto i=ups-1;~i;--i) if(up[i][u]!=up[i][v]){
            res=max({res,upw[i][u],upw[i][v]});
            u=up[i][u];v=up[i][v];
        }
        return max({res,upw[0][u],upw[0][v]});
    }
    tree(int _n):gr(_n),up(ups,vector<int>(_n)),upw(ups,vector<int>(_n)),h(_n){}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    while(T--) []{
        int n,m;cin>>n>>m;tree tr(n+1);
        dsu qwq(n+1);
        vector<tuple<int,int,int>> es(m);
        for(auto&[w,u,v]:es) cin>>u>>v>>w;
        sort(es.begin(),es.end());
        auto mst=0ll;
        vector<tuple<int,int,int>> ban;
        for(auto&[w,u,v]:es){
            if(qwq.findset(u)==qwq.findset(v)){
                ban.emplace_back(w,u,v);
                continue;
            }
            mst+=w;
            qwq.merge(u,v);
            tr.link(u,v,w);
        }
        if(ban.empty()||(int)(ban.size())+n-1!=m){
            cout<<-1<<'\n';
        }else{
            tr.init(1);
            auto ans=_inf;
            for(auto&[w,u,v]:ban){
                ans=min(ans,w-tr.path(u,v));
            }
            cout<<mst+ans<<'\n';
        }
    }();
    return 0;
}
