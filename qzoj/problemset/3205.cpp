#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lf=long double;
static constexpr auto _infl=1e16l;
class graph{
public:
    static auto gen(int n,int root,vector<tuple<int,int,lf>> es){
        auto ans=0.0l;
        while(true){
            vector<int> fr(n,-1);
            vector<lf> mn(n,_infl);
            mn[root]=0;
            for(auto&[u,v,w]:es) if(u!=v&&mn[v]>w) mn[v]=w,fr[v]=u;
            ans+=accumulate(mn.begin(),mn.end(),0.0l);
            auto cnt=0;
            vector<int> uf(n,-1),id(n,-1);
            cir(u,0,n){
                auto v=u;
                while(v!=root&&(uf[v]!=u)&&(id[v]<0)) uf[v]=u,v=fr[v];
                if(v!=root&&(id[v]<0)){
                    id[v]=cnt;
                    for(auto x=fr[v];x!=v;x=fr[x]) id[x]=cnt;
                    ++cnt;
                }
            }
            if(!cnt) return ans;
            cir(i,0,n) if(id[i]<0) id[i]=cnt,++cnt;
            for(auto&[u,v,w]:es) w-=mn[v],u=id[u],v=id[v];
            n=cnt;
            root=id[root];
        }
        assert(false);
    }
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n;cin>>n;
    const auto s=n;
    vector<tuple<int,int,lf>> es;
    vector<lf> uc(n),vc(n);
    cir(i,0,n){
        lf c,w;cin>>w>>c;
        uc[i]=c-1;vc[i]=w;
        es.emplace_back(s,i,w);
    }
    int m;cin>>m;
    cir(i,0,m){
        int u,v;lf w;cin>>u>>v>>w;--u;--v;
        es.emplace_back(u,v,w);
        vc[v]=min(vc[v],w);
    }
    auto ans=0.0l;
    cir(i,0,n) ans+=uc[i]*vc[i];
    cout<<fixed<<setprecision(2)<<ans+graph::gen(n+1,s,es)<<'\n';
    return 0;
}
