#include<bits/stdc++.h>
#define cir(i,a,b) for(auto i=a;i<b;++i)
using namespace std;
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
    constexpr auto inv(auto x) const{return qpow(x,MOD-2);}
} math;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    auto T=1;
    while(T--) [&]{
        int n,m;cin>>n>>m;
        vector<lint> f(m+1);
        f[0]=1;
        vector<vector<pair<int,lint>>> v(m);
        cir(i,0,n){
            int l,r,p,q;cin>>l>>r>>p>>q;--l;--r;
            (f[0]*=(q+MOD-p)*math.inv(q)%MOD)%=MOD;
            v[l].emplace_back(r+1,p*math.inv(q+MOD-p)%MOD);
        }
        cir(i,0,m){
            for(auto&[p,w]:v[i]) (f[p]+=f[i]*w)%=MOD;
        }
        cout<<f[m]<<'\n';
    }();
    return 0;
}
