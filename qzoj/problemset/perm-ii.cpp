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
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n;cin>>n;vector<int> a(n);
    for(auto&i:a) cin>>i;
    vector f(1<<n,vector<lint>(n,-1));
    auto success=[&](int s,int p){
        vector<int> a(n-1);
        cir(i,0,n) a.emplace_back((s>>i)&1);
        auto ok=is_sorted(a.begin(),a.end());
        if(p) ok&=(!a[p-1]);
        if(p+1<n) ok&=a[p+1];
        return ok;
    };
    vector<lint> invx(n*n+7);
    cir(i,0,n*n+7) invx[i]=math.inv(i);
    auto dfs=[&](auto __self,int s,int p){
        if(f[s][p]>-1) return f[s][p];
        f[s][p]=0;
        if(success(s,p)) return f[s][p];
        auto cnt=0;
        cir(i,0,n) if((s>>i)&1) cir(j,i+1,n) if((j!=p)&&(!((s>>j)&1))){
            f[s][p]+=__self(__self,s^(1<<i)^(1<<j),p);
            ++cnt;
        }
        cir(i,0,p) if((s>>i)&1){
            f[s][p]+=__self(__self,s^(1<<i)^(1<<p),i)+1;
            ++cnt;
        }
        cir(i,p+1,n) if(!((s>>i)&1)){
            f[s][p]+=__self(__self,s,i)+1;
            ++cnt;
        }
        (f[s][p])%=MOD;
        (f[s][p]*=invx[cnt])%=MOD;
        return f[s][p];
    };
    auto ans=0ll;
    cir(w,1,n+1){
        auto s=0;
        cir(i,0,n) if(a[i]>w) s|=(1<<i);
        (ans+=dfs(dfs,s,find(a.begin(),a.end(),w)-a.begin()))%=MOD;
    }
    cout<<(ans*invx[2])%MOD<<'\n';
    return 0;
}
