#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto _infl=(lint)(1e16l);
class graph{
public:
    static auto gen(int n,int root,vector<tuple<int,int,lint>> es){
        auto ans=0ll;
        while(true){
            vector<int> fr(n,-1);
            vector<lint> mn(n,_infl);
            mn[root]=0;
            for(auto&[u,v,w]:es) if(u!=v&&mn[v]>w) mn[v]=w,fr[v]=u;
            if(*max_element(mn.begin(),mn.end())==_infl) return -1ll;
            ans+=accumulate(mn.begin(),mn.end(),0ll);
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
    int n,m,r;cin>>n>>m>>r;--r;
    vector<tuple<int,int,lint>> es(m);
    for(auto&[u,v,w]:es) cin>>u>>v>>w,--u,--v;
    cout<<graph::gen(n,r,es)<<'\n';
    return 0;
}
