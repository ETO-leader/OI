#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto MOD=(int)(1e9+7);
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
    constexpr auto inv(auto x){
        return qpow(x,MOD-2);
    }
} math;
static constexpr auto iv2=math.inv(2);
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n,m;cin>>n>>m;
    vector f(n,vector<lint>(m+1));
    vector bpw(m+1,1ll),ibpw(m+2,1ll);
    cir(i,1,m+1) bpw[i]=bpw[i-1]*2%MOD;
    cir(i,1,m+2) ibpw[i]=ibpw[i-1]*iv2%MOD;
    f[0]=bpw;
    cir(i,1,n){
        vector<lint> pre(m+1);
        cir(p,1,m+1) pre[p]=(pre[p-1]+f[i-1][p]*ibpw[p+1]%MOD*p)%MOD;
        cir(ni,1,m+1){
            (f[i][ni]=
                (ni+1)*f[i-1][ni]+
                pre[ni-1]*bpw[ni]
            )%=MOD;
        }
    }
    cout<<f[n-1][m]<<'\n';
    return 0;
}
