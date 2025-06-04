#include<bits/stdc++.h>
#define cir(i,a,b) for(auto i=a;i<b;++i)
using namespace std;
using lint=long long;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    while(T--) []{
        int n;cin>>n;
        auto ans=0ll;
        cir(x,1ll,n+1) cir(y,1ll,n+1){
            const auto a=1;
            const auto b=y-x;
            const auto c=x*x-x*y-y*y;
            const auto delta=b*b-a*c*4;
            if(delta<0) continue;
            const auto v=(lint)(roundl(sqrtl(delta)));
            if(v*v!=delta) continue;
            const auto az0=-b-v;
            const auto az1=-b+v;
            if(az0>0&&(!(az0%(a*2)))){
                const auto z0=az0/(a*2);
                if(z0>0&&z0<n+1) ans+=(__gcd(__gcd(x,y),z0)==1);
            }
            if(delta&&(az1>0&&(!(az1%(a*2))))){
                const auto z1=az1/(a*2);
                if(z1>0&&z1<n+1) ans+=(__gcd(__gcd(x,y),z1)==1);
            }
        }
        cout<<ans<<'\n';
    }();
    return 0;
}
