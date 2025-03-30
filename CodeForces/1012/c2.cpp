#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto MOD=(int)(1e9+7);
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
static constexpr auto _inf=(int)(1e9+7);
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    while(T--) [&]{
        int n,l,k;cin>>n>>l>>k;
        vector<lint> ivx(l+7);
        cir(i,0,l+7) ivx[i]=math.inv(i);
        auto dfs=[&](auto __self,int left){
            if(!left) return vector<lint>(n);
            vector<lint> res(n);
            const auto px=__self(__self,left-1);
            vector<lint> up(n);
            auto prod=1ll;
            cir(i,0,left){
                (up[i%n]+=prod*ivx[left-i])%=MOD;
                (prod*=(MOD+1-ivx[left-i]))%=MOD;
            }
            cir(i,0,n){
                cir(j,0,n) (res[(i+j+1)%n]+=px[j]*up[i])%=MOD;
                (res[i]+=up[i])%=MOD;
            }
            return res;
        };
        const auto ans=dfs(dfs,l);
        for(auto&i:ans) cout<<i<<' ';
        cout<<'\n';
    }();
    return 0;
}
