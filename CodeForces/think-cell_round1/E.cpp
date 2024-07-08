#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr int MOD=998244353;
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
vector<lint> fct,ifct;
auto init(int n){
    fct.clear();ifct.clear();
    fct.resize(n,1);ifct.resize(n);
    cir(i,1,n) fct[i]=fct[i-1]*i%MOD;
    ifct[n-1]=inv(fct[n-1]);
    for(int i=n-2;~i;--i) ifct[i]=ifct[i+1]*(i+1)%MOD;
}
auto C(lint a,lint b){
    return fct[a]*ifct[b]%MOD*ifct[a-b]%MOD;
}

int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int T;cin>>T;
    while(T--){
        int n;cin>>n;init((n<<1)+7);
        cir(k,1,(n-1)/2+1){
            lint ans=1;
            for(int s=k*2;s<n+1;s+=k*2){
                (ans+=[n,k](int x){
                    return (C(n,x)+MOD-C(x+k*2-1,k*2-1))%MOD;
                }(n-s))%=MOD;
            }
            cout<<ans<<' ';
        }
        cout<<'\n';
    }
    return 0;
}
