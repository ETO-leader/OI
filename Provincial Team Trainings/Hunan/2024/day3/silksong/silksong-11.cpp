#include<bits/stdc++.h>
#define cir(i,a,b) for(auto i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto MOD=(int)(1e9+7);
class mathbase{
public:
    lint qpow(lint a,lint b) const{
        auto res=1ll;
        while(b){
            if(b&1) (res*=a)%=MOD;
            (a*=a)%=MOD;b>>=1;
        }
        return res;
    }
    lint inv(lint x) const{
        return qpow(x,MOD-2);
    }
} math;
inline uint64_t lowbit(uint64_t x){return x&(-x);}
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n,m;cin>>n>>m;
    const auto c=min(16,n/2);
    vector<vector<int>> gr(n);
    vector<uint64_t> sid(n);
    cir(i,0,m){
        int u,v;cin>>u>>v;--u;--v;
        gr[u].emplace_back(v);
        gr[v].emplace_back(u);
        sid[u]|=(1ull<<i);
        sid[v]|=(1ull<<i);
    }
    vector<lint> pw2(m+7,1);
    cir(i,1,m+7) pw2[i]=pw2[i-1]*2%MOD;
    auto ipw2=pw2;
    for(auto&x:ipw2) x=math.inv(x);
    auto mns=0ull,exts=0ull;
    mt19937 eng(251);
    [&]{
        vector<int> ord(n);
        for(int i=0;i<n;++i) ord[i]=i;
        auto mn=n+7;
        cir(i,0,500000){
            shuffle(ord.begin(),ord.end(),eng);
            auto ns=0ull,es=0ull;
            cir(i,0,c){
                ns|=(1ull<<ord[i]);
                es|=(1ull<<ord[i]);
                for(auto&v:gr[ord[i]]) es|=(1ull<<v);
            }
            const auto c=__builtin_popcountll(ns^es);
            if(mn>c){
                mn=c;mns=ns;exts=ns^es;
            }
        }
    }();
    vector<int> lnodes,rnodes;
    cir(i,0,n) (((mns>>i)&1)?lnodes:rnodes).emplace_back(i);
    sort(lnodes.begin(),lnodes.end());
    sort(rnodes.begin(),rnodes.end());
    const auto lc=(int)(lnodes.size());
    const auto rc=(int)(rnodes.size());
    typedef decltype(exts) stype_t;
    vector<int> rid(n);
    cir(i,0,rc) rid[rnodes[i]]=i;
    vector<int> cnt(1<<rc);
    auto nexts=0u;
    [&]{
        cir(i,0,n) if((exts>>i)&1) nexts|=(1<<rid[i]);
        vector<stype_t> f(1<<rc);
        cir(i,0,rc) f[1<<i]=sid[rnodes[i]];
        cir(s,0u,(1u<<rc)){
            if(s) f[s]=f[s^lowbit(s)]|f[lowbit(s)];
            const auto cnts=f[s];
            const auto ec=__builtin_popcountll(cnts);
            (cnt[nexts&s]+=ipw2[ec]*((__builtin_popcount(s)&1)?MOD-1:1)%MOD)%=MOD;
        }
    }();
    auto ans=0ll;
    [&]{
        vector<int> ecnt(n),nsid(n);
        const auto cexts=__builtin_popcount(nexts);
        vector<int> f(1<<cexts),g(1<<cexts);
        auto uc=-1;
        cir(i,0,n) if((nexts>>i)&1) nsid[++uc]=i;
        cir(s,0,(1<<cexts)) cir(i,0,cexts) if((s>>i)&1) f[s]|=(1<<nsid[i]); 
        cir(s,0u,(1<<lc)){
            fill(ecnt.begin(),ecnt.end(),0);
            auto cnts=0ull;
            cir(i,0,lc) if(s&(1<<i)) cnts|=sid[lnodes[i]];
            const auto ec=__builtin_popcountll(cnts);
            const auto w=ipw2[ec]*((__builtin_popcount(s)&1)?MOD-1:1)%MOD;
            cir(i,0,lc) if(s&(1<<i)) for(auto&v:gr[lnodes[i]]) ++ecnt[v];
            cir(i,0,cexts) g[1<<i]=ecnt[rnodes[nsid[i]]];
            cir(ns,0,(1<<cexts)){
                if(ns) g[ns]=(g[ns^lowbit(ns)]+g[lowbit(ns)])%MOD;
                (ans+=w*pw2[g[ns]]%MOD*cnt[f[ns]])%=MOD;
            }
        }
    }();
    cout<<ans*pw2[m]%MOD<<'\n';
    return 0;
}
