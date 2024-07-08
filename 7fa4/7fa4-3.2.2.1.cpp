#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
template<typename T>
struct dsu{
    vector<T> F;
    dsu(T _n):F(_n){iota(F.begin(),F.end(),0);}
    int findset(T x){return F[x]==x?x:F[x]=findset(F[x]);}
    void merge(T u,T v){F[findset(u)]=findset(v);}
};
template<typename T>
struct edge{int u,v;T w;};
const int MOD=1e9+7;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,m;cin>>n>>m;dsu<int> ds(n+1);
    vector<edge<lint>> ve(m+1);
    lint cnt=1,ans=0,neede=n-1;
    auto put=[&](){cout<<neede<<' '<<ans<<' '<<cnt<<'\n';};
    cir(i,0,m){
        int u,v;lint w;cin>>u>>v>>w;
        ve[i]={u,v,w};
    }
    cir(i,0,m){
        if(ve[i].w!=ve[i+1].w){
            if(ds.findset(ve[i].u)==ds.findset(ve[i].v)||(!neede))
                ans+=ve[i].w;
            else ds.merge(ve[i].u,ve[i].v),neede--;
        }else{
            int fu1=ds.findset(ve[i].u),fu2=ds.findset(ve[i].v);
            int fv1=ds.findset(ve[i+1].u),fv2=ds.findset(ve[i+1].v);
            if(fu1==fu2||(!neede)) ans+=ve[i].w;
            else if(fu1==fv1&&fu2==fv2||fu2==fv1&&fu1==fv2)
                ds.merge(ve[i].u,ve[i].v),neede--,
                    put(),(cnt*=2)%=MOD,++i,ans+=ve[i].w;
            else ds.merge(ve[i].u,ve[i].v),neede--;
        }
        put();
    }
    return 0;
}