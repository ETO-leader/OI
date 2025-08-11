#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto MOD=(int)(1e9+7);
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
class bit{
private:
    vector<lint> a;
    constexpr auto lowbit(auto x) const{return x&(-x);}
public:
    auto update(int u,lint w){
        for(++u;u<(int)(a.size());u+=lowbit(u)) (a[u]+=w)%=MOD;
    }
    auto query(int u) const{
        auto res=0ll;
        for(++u;u;u-=lowbit(u)) (res+=a[u])%=MOD;
        return res;
    }
    bit(int _n):a(_n+1){}
};
class stree{
private:
    vector<vector<int>> gr;
    vector<lint> val,sum;
    vector<int> fr,dfn,rdfn;
    int cnt;
    static constexpr auto ups=21;
    vector<vector<int>> up;
    vector<int> h;
    auto dfs(int u,int f=-1)->lint{
        up[u][0]=(f<0?0:f);h[u]=(f>-1?h[f]:0)+1;
        cir(i,1,ups) up[u][i]=up[up[u][i-1]][i-1];
        sum[u]=val[u];
        fr[u]=f;dfn[u]=++cnt;
        for(auto&i:gr[u]) if(i!=f) sum[u]+=dfs(i,u);
        rdfn[u]=cnt;
        return sum[u];
    }
public:
    auto link(int u,int v){
        gr[u].emplace_back(v);
        gr[v].emplace_back(u);
    }
    auto lca(int u,int v){
        if(h[u]<h[v]) swap(u,v);
        cir(i,0,ups) if((h[u]-h[v])&(1<<i))
            u=up[u][i];
        if(u==v) return u;
        for(auto i=ups-1;~i;--i) if(up[u][i]!=up[v][i])
            u=up[u][i],v=up[v][i];
        return up[u][0];
    }
    auto check(int r,vector<lint> _v){
        val=_v;dfs(r);
        return pair(sum,fr);
    }
    auto info(){return pair(dfn,rdfn);}
    stree(int _n):gr(_n),sum(_n),fr(_n),dfn(_n),rdfn(_n),cnt(-1),up(_n,vector<int>(ups)),h(_n){}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n,m;cin>>n>>m;
    vector<lint> w(n);
    for(auto&i:w) cin>>i;
    stree tr(n);
    vector<pair<int,int>> es;
    vector<vector<int>> vx(n);
    cir(i,0,n-1){
        int u,v;cin>>u>>v;--u;--v;
        tr.link(u,v);
        es.emplace_back(u,v);
        vx[u].emplace_back(v);
        vx[v].emplace_back(u);
    }
    auto ztr=tr;
    auto[zsum,zfr]=ztr.check(0,w);
    const auto[dfn,rdfn]=ztr.info();
    auto nsum=zsum;
    cir(i,0,n) nsum[i]=w[i]*math.inv(zsum[i])%MOD;
    bit bx(n+7),by(n+7);
    vector<lint> bval(n),cval(n);
    auto xsum=0ll;
    auto updval=[&](int i,lint w){
        (xsum+=w+MOD-bval[i])%=MOD;
        bx.update(dfn[i],w-bval[i]+MOD);
        bx.update(rdfn[i]+1,MOD-(w-bval[i])+MOD);
        bval[i]=w;
    };
    auto updxval=[&](int i,lint w){
        by.update(dfn[i],w-cval[i]+MOD);
        by.update(rdfn[i]+1,MOD-(w-cval[i])+MOD);
        cval[i]=w;
    };
    vector<lint> fw(n);
    const auto tsum=accumulate(w.begin(),w.end(),0ll)%MOD;
    vector<lint> dzsum(n);
    cir(i,0,n) dzsum[i]=math.inv(tsum+MOD-zsum[i]);
    auto update=[&](int u){
        for(auto&i:vx[u]) if(i!=zfr[u]) fw[i]=w[u]*dzsum[i]%MOD,updxval(i,fw[i]);
    };
    for(auto&x:vx){
        sort(x.begin(),x.end(),[&](int a,int b){return dfn[a]<dfn[b];});
    }
    vector<int> imp;
    const auto upl=(n<1e5+7&&m<1e5+7?50:2);
    cir(i,0,n) if(vx[i].size()<upl) update(i);else imp.emplace_back(i);
    cir(i,0,n) updval(i,nsum[i]);
    cir(i,0,m){
        int op;cin>>op;
        if(op==1){
            int k;cin>>k;--k;
            auto[x,y]=es[k];
            if(zfr[x]!=y) swap(x,y);
            const auto nsx=w[y]*math.inv(zsum[x]+w[y]+MOD-w[x])%MOD;
            const auto nsy=w[x]*math.inv(zsum[y])%MOD;
            (zsum[x]+=w[y]+MOD-w[x])%=MOD;
            updval(x,nsx);
            updval(y,nsy);
            swap(w[x],w[y]);
            dzsum[x]=math.inv(tsum+MOD-zsum[x]);
            dzsum[y]=math.inv(tsum+MOD-zsum[y]);
            if(vx[x].size()<upl) update(x);
            if(vx[y].size()<upl) update(y);
        }else if(op==2){
            int s,t;cin>>s>>t;--s;--t;
            const auto p=ztr.lca(s,t);
            auto add=0ll;
            if(upl==50) for(auto&u:imp){
                if(dfn[u]<dfn[p]&&rdfn[p]<rdfn[u]+1){
                    const auto x=ranges::upper_bound(vx[u],p,[&](int a,int b){return dfn[a]<dfn[b];})-vx[u].begin()-1;
                    (add+=w[u]*dzsum[vx[u][x]])%=MOD;
                }
            }
            cout<<(xsum+MOD*2-bx.query(dfn[s])-bx.query(dfn[t])+bx.query(dfn[p])+by.query(dfn[p])+add)%MOD<<'\n';
        }
    }
    return 0;
}