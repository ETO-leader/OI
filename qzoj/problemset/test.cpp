#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto MOD=998244353;
class mathbase{
public:
    const lint qpow(lint a,lint b) const{
        auto res=1ll;
        while(b){
            if(b&1) (res*=a)%=MOD;
            (a*=a)%=MOD;b>>=1;
        }
        return res;
    }
    const lint inv(lint x) const{
        return qpow(x,MOD-2);
    }
} math;
vector<int> ok;
lint dfs(int s,int p,int n,vector<vector<lint>>&f,vector<lint>&invx){
    if(f[s][p]>-1) return f[s][p];
    f[s][p]=0;
    auto cnt=0;
    ok.clear();
    for(auto i=n-1;~i;--i) if((i!=p)&&(!((s>>i)&1))) ok.emplace_back(i);
    cir(i,0,n) if((s>>i)&1) for(auto&j:ok){
        if(i>j) break;
        f[s][p]+=dfs(s^(1<<i)^(1<<j),p,n,f,invx);
        ++cnt;
    }
    cir(i,0,p) if((s>>i)&1){
        f[s][p]+=dfs(s^(1<<i)^(1<<p),i,n,f,invx)+1;
        ++cnt;
    }
    cir(i,p+1,n) if(!((s>>i)&1)){
        f[s][p]+=dfs(s,i,n,f,invx)+1;
        ++cnt;
    }
    (f[s][p])%=MOD;
    (f[s][p]*=invx[cnt])%=MOD;
    return f[s][p];
}
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n;cin>>n;vector<int> a(n);
    for(auto&i:a) cin>>i;
    vector<vector<lint>> f(1<<n,vector<lint>(n,-1));
    cir(i,0,n){
        auto s=0;
        cir(p,i+1,n) s|=(1<<p);
        f[s][i]=0;
    }
    vector<lint> invx(n*n+7);
    cir(i,0,n*n+7) invx[i]=math.inv(i);
    auto ans=0ll;
    cir(w,1,n+1){
        auto s=0;
        cir(i,0,n) if(a[i]>w) s|=(1<<i);
        (ans+=dfs(s,find(a.begin(),a.end(),w)-a.begin(),n,f,invx))%=MOD;
    }
    cout<<(ans*invx[2])%MOD<<'\n';
    return 0;
}
