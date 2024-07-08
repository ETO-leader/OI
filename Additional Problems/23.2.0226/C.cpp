#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
class dsu{
private:
    vector<int> F;
public:
    int findset(int x){
        return F[x]==x?x:F[x]=findset(F[x]);}
    void merge(int u,int v){
        F[findset(u)]=findset(v);}
    dsu(int _n):F(_n){iota(F.begin(),F.end(),0);}
};
struct edge_t{int u,v,w,id;};
void read_in(int m,int q,vector<edge_t>&E){
    cir(i,0,m){
        int u,v,w;cin>>u>>v>>w;
        E.push_back({u,v,w,q});
    }
    cir(i,0,q){
        int u,v,w;cin>>u>>v>>w;
        E.push_back({u,v,w,i});
    }
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,m,q;cin>>n>>m>>q;
    vector<edge_t> E;
    vector<string> ans(q+1,"No");
    read_in(m,q,E);
    sort(E.begin(),E.end(),
        [](edge_t&a,edge_t&b){return a.w<b.w;});
    dsu ds(n+1);
    for(auto&[u,v,w,id]:E){
        if(ds.findset(u)==ds.findset(v))
            continue;
        ans[id]="Yes";
        if(id==q) ds.merge(u,v);
    }
    cir(i,0,q) cout<<ans[i]<<'\n';
    return 0;
}
