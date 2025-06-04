#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto MOD=(int)(1e9+7);
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n,m;cin>>n>>m;
    const auto c=min(15,n/2);
    vector<vector<int>> gr(n);
    cir(i,0,m){
        int u,v;cin>>u>>v;--u;--v;
        gr[u].emplace_back(v);
        gr[v].emplace_back(u);
    }
    // vector<int> ord(n);
    // ranges::iota(ord,0);
    // mt19937 eng(251);
    // auto mn=n-c;
    // auto mns=0ull;
    // cir(i,0,500000){
    //     ranges::shuffle(ord,eng);
    //     auto ns=0ull,es=0ull;
    //     cir(i,0,15){
    //         ns|=(1ull<<ord[i]);
    //         es|=(1ull<<ord[i]);
    //         for(auto&v:gr[ord[i]]) es|=(1ull<<v);
    //     }
    //     const auto c=popcount(ns^es);
    //     if(mn>c){
    //         mn=c;mns=ns;
    //     }
    // }
    // vector<int> lnodes,rnodes;
    // cir(i,0,n) (((mns>>i)&1)?lnodes:rnodes).emplace_back(i);
    // ranges::sort(lnodes);
    // ranges::sort(rnodes);
    /*
        Bruteforce
    */
    vector<lint> pw2(m+7,1);
    cir(i,1,m+7) pw2[i]=pw2[i-1]*2%MOD;
    auto ans=0ll;
    cir(s,0,(1<<n)){
        set<pair<int,int>> cnt;
        cir(i,0,n) if((s>>i)&1){
            for(auto&v:gr[i]){
                cnt.emplace(min(i,v),max(i,v));
            }
        }
        (ans+=pw2[m-(int)(cnt.size())]*((__builtin_popcount(s)&1)?MOD-1:1))%=MOD;
    }
    cout<<ans<<'\n';
    return 0;
}
