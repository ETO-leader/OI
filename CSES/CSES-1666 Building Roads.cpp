#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
template<typename T>
struct dsu{
    vector<T> F;
    dsu(T _n):F(_n){iota(F.begin(),F.end(),0);}
    int findset(T x){return F[x]==x?x:F[x]=findset(F[x]);}
    void merge(T u,T v){F[findset(u)]=findset(v);}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,m;cin>>n>>m;dsu<int> ds(n+1);
    cir(i,0,m){
        int u,v;cin>>u>>v;ds.merge(u,v);
    }
    unordered_set<int> us;
    cir(i,1,n+1) us.insert(ds.findset(i));
    vector<int> v;
    for(auto&i:us) v.push_back(i);
    cout<<v.size()-1<<'\n';
    cir(i,0,v.size()-1) cout<<v[i]<<' '<<v[i+1]<<'\n';
    return 0;
}