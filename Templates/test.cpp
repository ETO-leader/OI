#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
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
    constexpr auto inv(auto x) const{
        return qpow(x,MOD-2);
    }
} math;
class hash_type{
public:
    auto operator()(const auto&x) const{
        auto res=(uint64_t)(x.second);
        for(auto&w:x.first) (res*=251)+=w;
        return res;
    }
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n;cin>>n;vector<int> d(n),p(n),q(n);
    cir(i,0,n) cin>>p[i]>>q[i]>>d[i],--d[i];
    cir(i,0,n) d[i]=min(d[i],n-1-i);
    vector<lint> inv(n+7);
    cir(i,0,n+7) inv[i]=math.inv(i);
    vector<unordered_map<pair<vector<int>,int>,lint,hash_type>> f(n);
    auto dfs=[&](auto __self,vector<int> a,int c,int u){
        if(u==n) return 1ll;
        c+=a[0];a.erase(a.begin());
        if(f[u].contains({a,c})) return f[u][{a,c}];
        auto res=0ll;
        const auto sum=accumulate(a.begin(),a.end(),0);
        // Type 1: Ins and nRmv
        [&]{
            a[d[u]]+=1;
            (res+=__self(__self,a,c,u+1)*p[u]%MOD*(MOD+1-q[u]))%=MOD;
            a[d[u]]-=1;
        }();
        // Type 2: Ins and Rmv
        [&]{
            a[d[u]]+=1;
            cir(i,0,(int)(a.size())) if(a[i]){
                --a[i];
                (res+=__self(__self,a,c,u+1)*p[u]%MOD*q[u]%MOD*inv[sum+1+c]*(a[i]+1))%=MOD;
                ++a[i];
            }
            a[d[u]]-=1;
        }();
        // Type 3: nIns and nRmv
        [&]{
            (res+=__self(__self,a,c,u+1)*(MOD+1-p[u])%MOD*(MOD+1-q[u]))%=MOD;
        }();
        // Type 4: nIns and Rmv
        [&]{
            cir(i,0,(int)(a.size())) if(a[i]){
                --a[i];
                (res+=__self(__self,a,c,u+1)*(MOD+1-p[u])%MOD*q[u]%MOD*inv[sum+c]*(a[i]+1))%=MOD;
                ++a[i];
            }
        }();
        return f[u][{a,c}]=res;
    };
    cout<<(MOD+1-dfs(dfs,vector<int>(n+1),0,0))%MOD<<'\n';
    return 0;
}
