#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
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
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n;cin>>n;vector<int> dep(n);
    cir(i,1,n){
        int f;cin>>f;--f;
        dep[i]=dep[f]+1;
    }
    vector<int> depc(n+7);
    vector<lint> fct(n+7,1);
    cir(i,1,n+7) fct[i]=fct[i-1]*i%MOD;
    cir(i,1,n+3) depc[i]=(depc[i-1]+math.inv(i+1)+MOD)%MOD;
    auto ans=n;
    cir(i,0,n) (ans+=depc[dep[i]])%=MOD;
    cout<<ans<<'\n';
    return 0;
}
