#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using ulint=unsigned long long;
static constexpr auto MOD=(int)(1e9+7);
constexpr auto qpow(ulint a,ulint b){
    auto res=1ull;
    while(b){
        if(b&1) (res*=a)%=MOD;
        (a*=a)%=MOD;b>>=1;
    }
    return res;
}
constexpr auto inv(ulint x){return qpow(x,MOD-2);}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int T;cin>>T;vector<ulint> iv;
    while(T--) [&](){
        ulint n,m,k;cin>>n>>m>>k;--k;
        if(n*m<k+1) return cout<<0<<'\n',void();
        while((int)(iv.size())<n+m)
            iv.push_back(inv(iv.size()));
        auto ans=1;
        cir(i,1,n){
            const auto anx=k/i;
            if(anx<m) (ans+=iv[i+anx])%=MOD;
        }
        cir(i,1,m){
            const auto anx=k/i;
            if(anx<n) (ans+=iv[i+anx])%=MOD;
        }
        cout<<ans<<'\n';
    }();
    return 0;
}
