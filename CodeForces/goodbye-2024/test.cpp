#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto MOD=998244353;
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
    int T;cin>>T;
    while(T--) [&]{
        int n,m,k;cin>>n>>m>>k;
        vector a(n,vector<lint>(m));
        for(auto&i:a) for(auto&x:i) cin>>x;
        auto rans=0ll;
        cir(w,1,k+1){
            const auto ca=a;
            for(auto&i:a[0]) if(i==-1) i=w;
            auto ans=0ll;
            cir(i,1,n){
                auto mx=0ll;
                cir(wx,1,k+1){
                    auto cx=ca[i];
                    for(auto&c:cx) if(c==-1) c=wx;
                    auto ansi=0ll;
                    cir(wi,1,k+1) ansi+=ranges::count(a[i-1],wi)*ranges::count(cx,wi);
                    if(ansi>mx) mx=ansi,a[i]=cx; 
                }
                ans+=mx;
            }
            clog<<w<<": "<<ans<<'\n';
            rans=max(rans,ans);
            a=ca;
        }
        cout<<rans<<'\n';
    }();
    return 0;
}
