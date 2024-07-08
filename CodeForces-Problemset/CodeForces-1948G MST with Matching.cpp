#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
class dsu{
private:
    vector<int> f;
public:
    auto findset(int u)->int{
        return f[u]==u?u:(f[u]=findset(f[u]));
    }
    auto merge(int u,int v){
        f[findset(u)]=findset(v);
    }
    dsu(int n):f(n){iota(f.begin(),f.end(),0);}
};
struct edge_t{int u,v,w;};
auto buildmst(const int n,vector<edge_t>&es){
    dsu ds(n);auto cnt=0,ans=0;
    for(const auto&[u,v,w]:es){
        if(ds.findset(u)==ds.findset(v))
            continue;
        ans+=w;++cnt;ds.merge(u,v);
    }
    return cnt==n-1?ans:-1;
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,c;cin>>n>>c;vector<edge_t> es;
    cir(i,0,n) cir(j,0,n){
        int w;cin>>w;
        if(w&&i<j) es.push_back({i,j,w});
    }
    auto ans=numeric_limits<int>::max();
    sort(es.begin(),es.end(),[](auto&a,auto&b){
        return a.w<b.w;
    });
    cir(i,0,(1<<n)){
        vector<edge_t> q;
        for(auto&[u,v,w]:es){
            if((i&(1<<u))||(i&(1<<v))){
                q.push_back({u,v,w});
            }
        }
        const auto w=buildmst(n,q);
        if(w>-1){
            ans=min(ans,__builtin_popcount(i)*c+w);
        }
    }
    cout<<ans<<'\n';
    return 0;
}
