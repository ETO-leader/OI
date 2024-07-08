#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using VI=vector<int>;
class dsu{
private:
    VI f;
public:
    auto findset(int u)->int{
        return f[u]==u?u:f[u]=findset(f[u]);
    }
    auto merge(int u,int v){
        f[findset(u)]=findset(v);
    }
    dsu(int _n):f(_n){iota(f.begin(),f.end(),0);}
};
struct edge_t{int u,v,w;};
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,m,k;cin>>n>>m>>k;
    vector<edge_t> es(m),stx;
    for(auto&[u,v,w]:es) cin>>u>>v>>w;
    // MST
    [&](){
        sort(es.begin(),es.end(),[](edge_t&a,
            edge_t&b){return a.w<b.w;});
        dsu ds(n+1);
        for(auto&[u,v,w]:es){
            if(ds.findset(u)!=ds.findset(v)){
                ds.merge(u,v);
                if(w) stx.push_back({u,v,w});
            }
        }
    }();
    // Rebuild
    try{
        int cnt=0;dsu ds(n+1);
        for(auto&[u,v,w]:stx) if(cnt<n-k-1){
            ++cnt;ds.merge(u,v);
        }
        for(auto&[u,v,w]:es) if(w&&cnt<n-k-1){
            if(ds.findset(u)!=ds.findset(v)){
                ds.merge(u,v);++cnt;
                stx.push_back({u,v,w});
            }
        }
        if(cnt<n-k-1) throw exception();
        for(auto&[u,v,w]:es) if(!w){
            if(ds.findset(u)!=ds.findset(v)){
                ds.merge(u,v);++cnt;
                stx.push_back({u,v,w});
            }
        }
        if(cnt<n-1) throw exception();
        for(auto&[u,v,w]:stx){
            cout<<u<<' '<<v<<' '<<w<<'\n';
        }
    }catch(exception&){
        cout<<"no solution\n";
    }
    return 0;
}
