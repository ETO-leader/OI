#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
auto&inf(cin);
auto&ouf(cout);
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
    int T=1;
    while(T--) []{
        int n,k,q;inf>>n>>k>>q;
        vector<int> b(n-k);
        for(auto&x:b) inf>>x,--x;
        vector<lint> preprod(k+7,1);
        cir(i,1,k+7) preprod[i]=preprod[i-1]*i%MOD*i%MOD;
        auto ipreprod=preprod;
        ipreprod[k+6]=math.inv(ipreprod[k+6]);
        for(auto i=k+5;~i;--i) ipreprod[i]=ipreprod[i+1]*(i+1)%MOD*(i+1)%MOD;
        vector<lint> fct(k+7,1);
        cir(i,1,k+7) fct[i]=fct[i-1]*i%MOD;
        vector<lint> g(k+1);
        cir(i,0,k+1) g[i]=fct[k-i]*preprod[k]%MOD*ipreprod[i]%MOD*ipreprod[k-i]%MOD;
        set<int> invalid;
        vector<int> pos(n-k);
        auto updpos=[&](int p){
            if(p-1>-1){
                if(invalid.count(p)) invalid.erase(p);
                if(pos[p-1]>pos[p]) invalid.emplace(p);
            }
            if(p+1<n-k){
                if(invalid.count(p+1)) invalid.erase(p+1);
                if(pos[p]>pos[p+1]) invalid.emplace(p+1);
            }
        };
        cir(i,0,n-k) pos[b[i]]=i;
        cir(i,0,n-k) updpos(i);
        vector<lint> pre(n);
        cir(i,0,n-k) if(n-k-1-i<k+1) (pre[i]+=g[n-k-1-i])%=MOD;
        cir(i,1,n) (pre[i]+=pre[i-1])%=MOD;
        auto calc=[&]{
            auto ans=0ll;
            if(n-k<k+1) (ans+=g[n-k])%=MOD;
            if(invalid.empty()) return (ans+pre[n-1])%MOD;
            return (ans+pre[*invalid.begin()-1])%MOD;
        };
        ouf<<calc()<<'\n';
        cir(i,0,q){
            int x,y;inf>>x>>y;--x;--y;
            swap(pos[b[x]],pos[b[y]]);
            updpos(b[x]);
            updpos(b[y]);
            swap(b[x],b[y]);
            ouf<<calc()<<'\n';
        }
    }();
    return 0;
}
