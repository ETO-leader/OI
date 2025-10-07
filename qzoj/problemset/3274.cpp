#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
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
    auto dfsht(int u,int c,vector<int>&cnt,int f=-1)->void{
        ++cnt[c];
        for(auto&[v,w]:gr[u]) if(v!=f&&(!ban[v])) dfsht(v,(c+w)%3,cnt,u);
    }
    auto divide(int u){
        const auto tsiz=dfssz(u);
        if(tsiz==1) return 1ll;
        const auto rt=dfsrt(u,tsiz);
        ban[rt]=true;
        vector<int> ucnt(3);
        ucnt[0]=1;
        auto res=1ll;
        for(auto&[v,w]:gr[rt]) if(!ban[v]){
            auto vcnt=vector<int>(3);
            dfsht(v,w,vcnt);
            cir(i,0,3) res+=(lint)(vcnt[i])*ucnt[(3-i)%3]*2;
            cir(i,0,3) ucnt[i]+=vcnt[i];
        }
        for(auto&[v,w]:gr[rt]) if(!ban[v]) res+=divide(v);
        return res;
    }
public:
    auto link(int u,int v,int w){
        gr[u].emplace_back(v,w%3);
        gr[v].emplace_back(u,w%3);
    }
    auto count(){
        return divide(0);
    }
    tree(int _n):gr(_n),siz(_n),ban(_n){}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n;cin>>n;tree gr(n);
    cir(i,0,n-1){
        int u,v,w;cin>>u>>v>>w;--u;--v;
        gr.link(u,v,w);
    }
    const auto ans=gr.count();
    const auto cnt=(lint)(n)*n;
    cout<<ans/__gcd(ans,cnt)<<'/'<<cnt/__gcd(ans,cnt)<<'\n';
    return 0;
}
