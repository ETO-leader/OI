#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
class dsu{
private:
    vector<int> f,siz;
public:
    auto findset(auto u)->int{
        return f[u]==u?u:f[u]=findset(f[u]);
    }
    auto merge(int u,int v){
        u=findset(u);v=findset(v);
        siz[v]+=siz[u];f[u]=v;
    }
    auto size(auto u) const{return siz[u];}
    dsu(int _n):f(_n),siz(_n,1){iota(f.begin(),f.end(),0);}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n,m,k;cin>>n>>m>>k;
    queue<pair<int,int>> q;
    vector<unordered_map<int,int>> gr(n);
    dsu gsiz(n);
    auto emplace_edge=[&](int u,int v,int w){
        clog<<"+ "<<u<<' '<<v<<' '<<w<<'\n';
        if(gr[v].count(w)) q.emplace(u,gr[v][w]);
        else gr[v][w]=u;
    };
    cir(i,0,m){
        int u,v,w;cin>>u>>v>>w;--u;--v;
        emplace_edge(u,v,w);
    }
    auto merge=[&](int u,int v){
        u=gsiz.findset(u);v=gsiz.findset(v);
        if(u==v) return;
        if(gsiz.size(v)>gsiz.size(u)) swap(u,v);
        for(auto&[wx,vx]:gr[v]) emplace_edge(vx,u,wx);
        gsiz.merge(v,u);
    };
    while(!q.empty()){
        const auto[u,v]=q.front();q.pop();
        merge(u,v);
    }
    auto ans=0ll;
    cir(i,0,n) if(gsiz.findset(i)==i){
        const auto siz=(int64_t)(gsiz.size(i));
        ans+=siz*(siz-1)/2;
    }
    cout<<ans<<'\n';
    return 0;
}
