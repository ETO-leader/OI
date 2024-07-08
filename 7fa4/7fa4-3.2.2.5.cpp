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
struct edge{int u,v,w,id;};
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,m;cin>>n>>m;vector<edge> G(m),E(m+1);
    cir(i,0,m) cin>>G[i].u>>G[i].v>>G[i].w,G[i].id=i+1;
    cir(i,0,m) E[i+1]=G[i];
    sort(G.begin(),G.end(),[](edge&a,edge&b){return a.w<b.w;});
    dsu<int> ds(n+1),ch(n+1);vector<bool> Ct(m+1);
    cir(i,0,m){
        vector<edge> v;
        while(i!=m-1&&G[i].w==G[i+1].w) v.push_back(G[i]),++i;
        v.push_back(G[i]);
        for(auto&j:v) Ct[j.id]=(ds.findset(j.u)!=ds.findset(j.v));
        for(auto&j:v) ds.merge(j.u,j.v);
    }
    int q;cin>>q;
    cir(i,0,q){
        int qi,ct=true,cnt=0;cin>>qi;
        vector<int> Cid(qi);
        for(auto&i:Cid) cin>>i,ct&=Ct[i];
        if(!ct){cout<<0;continue;}
        for(auto&j:Cid){
            if(ch.findset(E[j].u)==ch.findset(E[j].v)){cout<<0;goto erase;}
            else ch.merge(E[j].u,E[j].v);
            ++cnt;
        }
        cout<<1;
        erase:for(auto&j:Cid) ch.F[E[j].u]=E[j].u,ch.F[E[j].v]=E[j].v;
    }
    cout<<'\n';
    return 0;
}