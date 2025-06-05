#include<bits/stdc++.h>
#define cir(i,a,b) for(auto i=a;i<b;++i)
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
constexpr auto lowbit(auto x){return x&(-x);}
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n,m;cin>>n>>m;
    const auto c=min(15,n/2);
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
        ranges::iota(ord,0);
        auto mn=n+7;
        cir(i,0,500000){
            ranges::shuffle(ord,eng);
            auto ns=0ull,es=0ull;
            cir(i,0,c){
                ns|=(1ull<<ord[i]);
                es|=(1ull<<ord[i]);
                for(auto&v:gr[ord[i]]) es|=(1ull<<v);
            }
            const auto c=popcount(ns^es);
            if(mn>c){
                mn=c;mns=ns;exts=ns^es;
            }
        }
    }();
    vector<int> lnodes,rnodes;
    cir(i,0,n) (((mns>>i)&1)?lnodes:rnodes).emplace_back(i);
    ranges::sort(lnodes);
    ranges::sort(rnodes);
    const auto lc=(int)(lnodes.size());
    const auto rc=(int)(rnodes.size());
    using stype_t=decltype(exts);
    vector<int> rid(n);
    cir(i,0,rc) rid[rnodes[i]]=i;
    vector<int> cnt(1<<rc);
    auto nexts=0;
    [&]{
        cir(i,0,n) if((exts>>i)&1) nexts|=(1<<rid[i]);
        vector<stype_t> f(1<<rc);
        cir(i,0,rc) f[1<<i]=sid[rnodes[i]];
        cir(s,0u,(1<<rc)){
            if(s) f[s]=f[s^lowbit(s)]|f[lowbit(s)];
            const auto cnts=f[s];
            const auto ec=popcount(cnts);
            (cnt[nexts&s]+=ipw2[ec]*((popcount(s)&1)?MOD-1:1)%MOD)%=MOD;
        }
    }();
    auto ans=0ll;
    [&]{
        vector<int> ecnt(n);
        cir(s,0u,(1<<lc)){
            ranges::fill(ecnt,0);
            auto cnts=0ull;
            cir(i,0,lc) if(s&(1<<i)) cnts|=sid[lnodes[i]];
            const auto ec=popcount(cnts);
            const auto w=ipw2[ec]*((popcount(s)&1)?MOD-1:1)%MOD;
            cir(i,0,lc) if(s&(1<<i)) for(auto&v:gr[lnodes[i]]) ++ecnt[v];
            for(auto ns=nexts;;ns=(ns-1)&nexts){
                auto ucnt=0;
                cir(i,0,rc) if((ns>>i)&1) ucnt+=ecnt[rnodes[i]];
                (ans+=w*pw2[ucnt]%MOD*cnt[ns])%=MOD;
                if(!ns) break;
            }
        }
    }();
    cout<<ans*pw2[m]%MOD<<'\n';
    return 0;
}
