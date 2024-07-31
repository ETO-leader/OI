#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto MOD=998244353;
static constexpr auto _inf=(int)(1e9+7);
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,x,m;cin>>n>>x>>m;
    constexpr auto maxfib=55;
    constexpr auto maxfibp=30;
    vector fib(maxfibp,1);
    cir(i,2,maxfibp) fib[i]=fib[i-1]+fib[i-2];
    vector cost(n*maxfib+7,_inf);
    cost[0]=0;
    for(auto&w:fib){
        cir(i,w,n*maxfib+7) cost[i]=min(cost[i],cost[i-w]+1);
    }
    vector f(n+1,vector<lint>(n*maxfib+7));
    f[0][0]=1; 
    cir(p,0,x) cir(i,1,n+1) cir(j,fib[p],n*maxfib+7){
        (f[i][j]+=f[i-1][j-fib[p]])%=MOD;
    }
    auto ans=0ll;
    cir(i,0,n*maxfib+7) (ans+=f[n][i]*(cost[i]==m))%=MOD;
    cout<<ans<<'\n';
    return 0;
}
