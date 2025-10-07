#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto _inf=(int)(1e9+7);
class tree{
private:
    vector<vector<pair<int,int>>> gr;
    vector<int> siz,ban;
    auto dfssz(int u,int f=-1)->int{
        siz[u]=1;
        for(auto&[v,w]:gr[u]) if(v!=f&&(!ban[v])) siz[u]+=dfssz(v,u);
        return siz[u];
    }
    auto dfsrt(int u,const int tsiz,int f=-1)->int{
        auto umx=-1;
        for(auto&[v,w]:gr[u]) if(v!=f&&(!ban[v])){
            const auto vw=dfsrt(v,tsiz,u);
            if(vw>-1) return vw;
            umx=max(umx,siz[v]);
        }
        if(max(umx,tsiz-siz[u])<tsiz/2+1) return u;
        return -1;
    }
    auto dfsht(int u,lint c,int dep,map<lint,int>&cnt,int f=-1)->void{
        ++dep;
        if(cnt.count(c)) cnt[c]=min(cnt[c],dep);
        else cnt[c]=dep;
        for(auto&[v,w]:gr[u]) if(v!=f&&(!ban[v])) dfsht(v,c+w,dep,cnt,u);
    }
    auto divide(int u,const int k){
        const auto tsiz=dfssz(u);
        if(tsiz==1) return _inf;
        const auto rt=dfsrt(u,tsiz);
        ban[rt]=true;
        map<lint,int> cnt;
        cnt[0]=0;
        auto res=_inf;
        for(auto&[v,w]:gr[rt]) if(!ban[v]){
            map<lint,int> vtr;
            dfsht(v,w,0,vtr);
            for(auto&[x,y]:vtr) if(cnt.count(k-x)) res=min(res,y+cnt[k-x]);
            for(auto&[x,y]:vtr){
                if(cnt.count(x)) cnt[x]=min(cnt[x],y);
                else cnt[x]=y;
            }
        }
        for(auto&[v,w]:gr[rt]) if(!ban[v]) res=min(res,divide(v,k));
        return res;
    }
public:
    auto link(int u,int v,int w){
        gr[u].emplace_back(v,w);
        gr[v].emplace_back(u,w);
    }
    auto count(const int k){
        return divide(0,k);
    }
    tree(int _n):gr(_n),siz(_n),ban(_n){}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n,k;cin>>n>>k;tree gr(n);
    cir(i,0,n-1){
        int u,v,w;cin>>u>>v>>w;
        gr.link(u,v,w);
    }
    const auto ans=gr.count(k);
    cout<<(ans<_inf?ans:-1)<<'\n';
    return 0;
}
