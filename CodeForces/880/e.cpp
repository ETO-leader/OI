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
    constexpr auto inv(auto x){return qpow(x,MOD-2);}
} math;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    auto T=1;
    while(T--) [&]{
        int n,m;cin>>n>>m;
        vector<int> a(n);
        for(auto&x:a) cin>>x;
        const auto cnt=(int)(set(a.begin(),a.end()).size());
        vector<lint> winv(m+7);
        cir(i,1,m+7) winv[i]=math.inv(i);
        vector f(cnt+1,vector<lint>(m+1));
        vector g(cnt+1,vector<lint>(m+1));
        vector h(cnt+1,vector<lint>(m+1));
        cir(i,1,cnt+1) cir(j,0,m-cnt+1){
            f[i][j]=(i-1)*winv[i+j]%MOD*(f[i-1][j]+3)%MOD;
            (f[i][j]+=winv[i+j]*(f[i-1][j]+1))%=MOD;
            if(j) (f[i][j]+=winv[i+j]*j%MOD*(f[i][j-1]+2))%=MOD;
        }
        cir(i,0,cnt+1) cir(j,0,m-cnt+1){
            g[i][j]=winv[i+j+1]*f[i][j]%MOD;
            if(i) (g[i][j]+=winv[i+j+1]*i%MOD*(g[i-1][j]+3))%=MOD;
            if(j) (g[i][j]+=winv[i+j+1]*j%MOD*(g[i][j-1]+2))%=MOD;
        }
        cir(i,1,cnt+1) cir(j,0,m-cnt+1){
            h[i][j]=winv[i+j+1]*(h[i-1][j]+1)%MOD;
            (h[i][j]+=(i-1)*winv[i+j+1]%MOD*(g[i-1][j]+3))%=MOD;
            if(j) (h[i][j]+=j*winv[i+j+1]%MOD*(g[i][j-1]+2))%=MOD;
            (h[i][j]+=winv[i+j+1]*(f[i][j]+2))%=MOD;
        }
        const auto ans=(
            (n-cnt)+
            winv[m+1]*(f[cnt][m-cnt]+1)+
            winv[m+1]*(h[cnt-1][m-cnt]+1)+
            winv[m+1]*(cnt-1)%MOD*(g[cnt-1][m-cnt]+3)+
            winv[m+1]*(m-cnt)%MOD*(g[cnt][m-cnt-1]+2)
        )%MOD;
        cout<<ans<<'\n';
    }();
    return 0;
}
