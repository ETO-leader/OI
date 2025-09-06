#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
ifstream inf("calc.in");
ofstream ouf("calc.out");
using lint=long long;
static constexpr auto MOD=998244353;
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
int main(){
    ios::sync_with_stdio(false),inf.tie(nullptr);
    int T;inf>>T;
    while(T--) []{
        lint n,m;inf>>n>>m;
        auto fctn=1ll,ifctn=1ll;
        cir(i,0,n*m) (fctn*=(i+1))%=MOD;
        cir(i,0,n) (ifctn*=(i+1))%=MOD;
        cir(i,0,m) (ifctn*=(i+1))%=MOD;
        ouf<<fctn*math.inv(ifctn)%MOD<<'\n';
    }();
    return 0;
}
