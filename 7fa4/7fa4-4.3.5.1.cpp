#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto MOD=(int)(1e9+7);
class mathbase{
public:
    constexpr auto qpow(auto a,auto b){
        auto res=(decltype(a))(1);
        while(b){
            if(b&1) (res*=a)%=MOD;
            (a*=a)%=MOD;b>>=1;
        }
        return res;
    }
    constexpr auto inv(auto x){return qpow((lint)(x),MOD-2);}
} math;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n;cin>>n;vector<lint> f(n+1);
    f[0]=1;
    cir(i,1,n) f[i]=(i*f[i-1]+n)%MOD*math.inv(n-i)%MOD;
    for(auto i=n-1;~i;--i) (f[i]+=f[i+1])%=MOD;
    copy(f.begin(),f.end(),ostream_iterator<lint>(cout,"\n"));
    return 0;
}
