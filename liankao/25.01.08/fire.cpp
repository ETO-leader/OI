#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
ifstream fcin("fire.in");
ofstream fcout("fire.out");
class fileio{
public:
    ~fileio(){
        fcin.close();fcout.close();
    }
} use_fileio;
using lint=long long;
static constexpr auto MOD=998244353;
class mathbase{
public:
    constexpr auto qpow(lint a,auto b){
        auto res=1ll;
        while(b){
            if(b&1) (res*=a)%=MOD;
            (a*=a)%=MOD;b>>=1;
        }
        return res;
    }
    constexpr auto inv(auto x){return qpow(x,MOD-2);}
} math;
class hashvec{
public:
    auto operator()(const vector<int>&x) const{
        auto res=(size_t)(0);
        for(auto&w:x) (res*=13)^=w;
        return res;
    }

};
int main(){
    ios::sync_with_stdio(false),fcin.tie(nullptr);
    int n,m;fcin>>n>>m;
    vector<tuple<int,int,lint>> es;
    cir(i,0,m){
        int u,v,p,q;fcin>>u>>v>>p>>q;--u;--v;
        const auto px=p*math.inv(q)%MOD;
        es.emplace_back(u,v,(MOD+1-px));
    }
    vector<lint> f(1<<n);
    f[(1<<n)-1]=0;
    vector<unordered_map<vector<int>,lint,hashvec>> g(m+1),inc(m+1);
    vector<unordered_set<vector<int>,hashvec>> vis(m+1);
    auto init=[&](auto __self,int x,vector<int> cur){
        if(x>m-1) return;
        if(vis[x].count(cur)) return;
        vis[x].emplace(cur);
        const auto[u,v,p]=es[x];
        if(cur[u]==cur[v]){
            ++inc[x+1][cur];
            __self(__self,x+1,cur);
        }else{
            auto ncur=cur;
            const auto colv=cur[v];
            cir(i,0,n) if(cur[i]==colv) ncur[i]=ncur[u];
            vector<int> col(n,-1);
            auto cnt=0;
            cir(i,0,n) if(col[ncur[i]]==-1) col[ncur[i]]=cnt++;
            for(auto&x:ncur) x=col[x];
            ++inc[x+1][cur];
            ++inc[x+1][ncur];
            __self(__self,x+1,cur);
            __self(__self,x+1,ncur);
        }
    };
    auto dfs=[&](auto __self,int x,vector<int> cur){
        if(--inc[x][cur]) return;
        if(x>m-1) return;
        const auto[u,v,p]=es[x];
        if(cur[u]==cur[v]){
            (g[x+1][cur]+=g[x][cur])%=MOD;
            return __self(__self,x+1,cur);
        }else{
            auto ncur=cur;
            const auto colv=cur[v];
            cir(i,0,n) if(cur[i]==colv) ncur[i]=ncur[u];
            vector<int> col(n,-1);
            auto cnt=0;
            cir(i,0,n) if(col[ncur[i]]==-1) col[ncur[i]]=cnt++;
            for(auto&x:ncur) x=col[x];
            (g[x+1][cur]+=g[x][cur]*p)%=MOD;
            (g[x+1][ncur]+=g[x][cur]*(MOD+1-p))%=MOD;
            __self(__self,x+1,cur);
            __self(__self,x+1,ncur);
        }
    };
    vector<int> a(n);
    iota(a.begin(),a.end(),0);
    init(init,0,a);
    inc[0][a]=1;g[0][a]=1;
    dfs(dfs,0,a);
    vector<pair<vector<int>,lint>> gx;
    for(auto&[a,w]:g[m]) gx.emplace_back(a,w);
    for(auto s=(1<<n)-2;~s;--s){
        auto sumvaild=0ll;
        vector<int> fr(n),ap(n);
        for(auto&[st,w]:gx){
            fill(fr.begin(),fr.end(),0);
            fill(ap.begin(),ap.end(),0);
            cir(i,0,n) fr[st[i]]|=(1<<i);
            cir(i,0,n) if(s&(1<<i)) ap[st[i]]=true;
            auto ns=s;
            cir(i,0,n) if(ap[i]) ns|=fr[i];
            if(ns!=s) (f[s]+=f[ns]*w)%=MOD,(sumvaild+=w)%=MOD;
        }
        ((++f[s])*=math.inv(sumvaild))%=MOD;
    }
    cir(u,0,n) fcout<<f[1<<u]<<' ';
    fcout<<'\n';
    return 0;
}
