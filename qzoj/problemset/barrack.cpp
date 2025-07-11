#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto _infl=(lint)(2e18l);
static constexpr auto MOD=998244353;
class mathbase{
public:
    constexpr auto qpow(lint a,auto b) const{
        auto res=1ll;
        while(b){
            if(b&1) (res*=a)%=MOD;
            (a*=a)%=MOD;b>>=1;
        }
        return res;
    }
    constexpr auto inv(auto x) const{
        return qpow(x,MOD-2);
    }
} math;
class tree{
private:
    vector<vector<pair<int,int>>> gr;
    vector<int> siz,xdep;
    vector<tuple<int,int,int>> es;
    auto init(int u,int f=-1)->int{
        siz[u]=1;xdep[u]=1;
        for(auto&[v,w]:gr[u]) if(v!=f){
            es.emplace_back(u,v,w);
            siz[u]+=init(v,u);
            xdep[u]=max(xdep[u],xdep[v]+1);
        }
        return siz[u];
    }
    vector<lint> f;
    lint ans,prew;
    vector<lint> wf;
    int cnt;
    auto allocw(int p){
        const auto res=cnt;
        cnt+=p;
        return res;
    }
    const int n,k;
    auto dfs(int u)->void{
        for(auto&[v,w]:gr[u]){
            dfs(v);
            f[u]+=f[v]+1ll*siz[v]*w;
        }
    }
    auto check(int u,lint prew,vector<lint>::iterator w)->lint{
        sort(gr[u].begin(),gr[u].end(),[&](auto a,auto b){
            return xdep[a.first]>xdep[b.first];
        });
        if(gr[u].empty()&&k==1) ans=min(ans,prew);
        if(gr[u].empty()) return *w=0,0ll;
        auto ex=check(gr[u][0].first,prew+f[u]-f[gr[u][0].first]-1ll*siz[gr[u][0].first]*gr[u][0].second+1ll*(n-siz[gr[u][0].first])*gr[u][0].second,w+1);
        ex+=f[u]-f[gr[u][0].first]-1ll*siz[gr[u][0].first]*gr[u][0].second;
        *w=f[u]-ex;
        if(k>1){
            if(xdep[u]>k-1) ans=min(ans,*(w+k-1)+prew+ex);
        }else{
            ans=min(ans,f[u]+prew);
        }
        cir(i,1,(int)(gr[u].size())){
            auto nw=wf.begin()+allocw(xdep[gr[u][i].first]);
            const auto nex=check(gr[u][i].first,prew+f[u]-f[gr[u][i].first]-1ll*siz[gr[u][i].first]*gr[u][i].second+1ll*(n-siz[gr[u][i].first])*gr[u][i].second,nw);
            if(k>1) cir(udep,0,xdep[gr[u][i].first]){
                if(k-2-udep>-1&&k-2-udep<xdep[u]){
                    ans=min(ans,prew+*(nw+udep)+*(w+k-2-udep)+nex+ex-f[gr[u][i].first]-1ll*siz[gr[u][i].first]*gr[u][i].second);
                }
            }
            cir(udep,0,xdep[gr[u][i].first]){
                *(w+udep+1)=min(*(w+udep+1),*(nw+udep)+f[u]-f[gr[u][i].first]-1ll*siz[gr[u][i].first]*gr[u][i].second+nex-ex);
            }
        }
        return ex;
    }
public:
    auto link(int u,int v,lint _w){
        gr[u].emplace_back(v,_w);
        gr[v].emplace_back(u,_w);
    }
    auto check(){
        init(0);
        for(auto&x:gr) x.clear();
        for(auto&[u,v,w]:es) gr[u].emplace_back(v,w);
        dfs(0);
        allocw(xdep[0]);
        check(0,0,wf.begin());
        return ans;
    }
    tree(int _n,int _k):n(_n),gr(_n),siz(_n),f(_n),k(_k),ans(_infl),xdep(_n),wf(_n+7),cnt(0){}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n,k;cin>>n>>k;tree gr(n,k);
    cir(i,0,n-1){
        int u,v;int64_t w;cin>>u>>v>>w;--u;--v;
        gr.link(u,v,w);
    }
    const auto ans=gr.check();
    if(ans>_infl-1) cout<<"-1"<<'\n';
    else cout<<(int64_t)(ans%MOD*math.inv(n)%MOD)<<'\n';
    return 0;
}
