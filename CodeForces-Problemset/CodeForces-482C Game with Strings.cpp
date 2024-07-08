#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lf=long double;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n;cin>>n;
    vector<string> str(n);
    for(auto&i:str) cin>>i;
    const int m=str.front().size();
    vector<lf> cnt(1<<m);
    vector<int64_t> g(1<<m);
    cir(i,0,n){
        cir(j,0,n) if(i!=j){
            auto ins=0;
            cir(p,0,m) if(str[i][p]==str[j][p]){
                ins|=(1<<p);
            }
            g[ins]|=(1ll<<i)|(1ll<<j);
        }
    }
    for(auto s=(1<<m)-1;~s;--s){
        cir(i,0,m) g[s]|=g[s|(1<<i)];
        cnt[s]=__builtin_popcountll(g[s]);
    }
    vector<lf> f(1<<m);
    cir(s,0,(1<<m)-1){
        const auto chs=__builtin_popcount(s);
        const auto p=cnt[s]/n;
        cir(nx,0,m) if(!(s&(1<<nx))){
            f[s|(1<<nx)]+=(f[s]+p)/(chs+1);
        }
    }
    cout<<fixed<<setprecision(16)<<f[(1<<m)-1]<<'\n';
    return 0;
}