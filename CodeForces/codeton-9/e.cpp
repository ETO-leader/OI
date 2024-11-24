#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto MOD=998244353;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    while(T--) []{
        int n;cin>>n;
        vector<lint> f(n+1);
        cir(i,4,n+1) f[i]=(1ll*(i-2)*(i-3)/2+i-3)%MOD;
        auto pre=(n<4?0ll:f[4]*4)%MOD;
        cir(i,5,n+1){
            (f[i]+=pre)%=MOD;(pre+=f[i]*i)%=MOD;
        }
        cir(i,5,n+1) (f[i]+=f[i-1])%=MOD;
        println("{}",(f[n]+n-1)%MOD);
    }();
    return 0;
}
