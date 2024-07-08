#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
#pragma GCC target("avx,avx2,sse,sse2,sse3,ssse3,sse4,abm,mmx")
#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto MOD=998244353;
constexpr auto qpow(lint a,lint b){
    lint res=1;
    while(b){
        if(b&1) (res*=a)%=MOD;
        (a*=a)%=MOD;b>>=1;
    }
    return res;
}
constexpr auto inv(lint x){
    return qpow(x,MOD-2);
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    lint n;int k,p;cin>>n>>p>>k;
    vector<lint> pwp(k+7);
    cir(i,0,k+7) pwp[i]=qpow(p,i);
    const auto pwn=qpow(p,n);
    cir(kx,0,k+1){
        lint ansi=1;
        cir(j,0,kx){
            (ansi*=qpow(pwn-pwp[j],2)*
                inv((pwp[kx]-pwp[j]+MOD)%MOD)%MOD)%=MOD;
        }
        cout<<ansi<<' ';
    }
    cout<<'\n';
    return 0;
}
