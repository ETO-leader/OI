#include<bits/stdc++.h>
using namespace std;
const string IMP="IMPOSSIBLE";
template<typename T>
struct dsu{
    vector<T> F;
    T findset(int x){return F[x]==x?x:F[x]=findset(F[x]);}
    void merge(int u,int v){F[findset(u)]=findset(v);}
    dsu(int _sz):F(_sz){iota(F.begin(),F.end(),0);}
};
struct edge{int u,v,w;};
void NoSolution(){cout<<IMP<<'\n';exit(0);};
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,m;cin>>n>>m;dsu<int> ds(n+1);
    vector<edge> G(m);
    for(auto&i:G) cin>>i.u>>i.v>>i.w;
    sort(G.begin(),G.end(),[](edge&a,edge&b){return a.w<b.w;});
    long long ans=0,cnt=0;
    for(auto&i:G){
        if(ds.findset(i.u)==ds.findset(i.v)) continue;
        ++cnt;ans+=i.w;ds.merge(i.u,i.v);
    }
    if(cnt!=n-1) NoSolution();
    cout<<ans<<'\n';
    return 0;
}
