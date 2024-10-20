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
    constexpr auto inv(lint x){return qpow(x,MOD-2);}
} math;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    while(T--) [&](){
        int n;cin>>n;
        vector<lint> a(n),p(n);
        for(auto&i:a) cin>>i;
        for(auto&i:p) cin>>i,(i*=math.inv(10000))%=MOD;
        const auto mxa=1<<((int)(ceil(log2((*ranges::max_element(a))+1))));
        vector<lint> f(mxa),g(mxa);f[0]=1;
        cir(i,0,n){
            ranges::copy(f,g.begin());
            ranges::fill(f,0);
            cir(w,0,mxa){
                (f[w]+=g[w]*(MOD+1-p[i]))%=MOD;
                (f[w^a[i]]+=g[w]*p[i])%=MOD;
            }
        }
        auto ans=0ll;
        cir(i,0,mxa) (ans+=i*i%MOD*f[i])%=MOD;
        println("{}",ans);
    }();
    return 0;
}
