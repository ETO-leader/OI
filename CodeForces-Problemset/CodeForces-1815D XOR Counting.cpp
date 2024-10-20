#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto MOD=998244353;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    unordered_map<lint,lint> fx,gx;
    gx[0]=1;fx[0]=0;
    while(T--) [&](){
        lint n,m;cin>>n>>m;
        if(m==1) return println("{}",n%MOD);
        if(m>2) return println("{}",(n/2+(n&1))%MOD*((n/2+1)%MOD)%MOD);
        auto g=[&](auto __self,lint nx)->lint {
            if(nx<0) return 0ll;
            if(gx.count(nx)) return gx[nx];
            return gx[nx]=(nx&1?__self(__self,nx/2):(__self(__self,nx/2)+__self(__self,nx/2-1))%MOD);
        };
        auto f=[&](auto __self,lint nx)->lint {
            if(nx<0) return 0ll;
            if(fx.count(nx)) return fx[nx];
            return fx[nx]=(nx&1?(__self(__self,nx/2)*2+g(g,nx/2))%MOD:(__self(__self,nx/2)+__self(__self,nx/2-1))*2%MOD);
        };
        println("{}",f(f,n));
    }();
    return 0;
}
