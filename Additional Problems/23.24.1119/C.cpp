#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
using VI=vector<lint>;
static constexpr int MOD=998244353;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n;cin>>n;VI a(n),lim(n+1),cnt(n+1);
    for(auto&i:a) cin>>i,++cnt[i];
    cir(i,0,n+1) for(auto&x:cnt){
        lim[i]+=min<lint>(x,i);
    }
    lim[0]=n;
    vector<vector<VI>> D(2,
        vector<VI>(n+1,VI(n+1)));
    D[0][n][0]=1;lint ans=0;
    cir(x,1,n+1){
        auto&d=D[x&1];
        auto&pre=D[(x&1)^1];
        for(int i=lim[x-1]-1;~i;--i){
            cir(j,i*(x-1),lim[x-1]+1){
                (pre[i][j]+=pre[i+1][j])%=MOD;
            }
            cir(j,max<lint>(0,i*(x-2)),n+1) d[i][j]=0;
        }
        cir(i,0,n+1) d[n][i]=0;
        cir(i,1,lim[x]+1) cir(j,i*x,lim[x]+1){
            (d[i][j]+=pre[i][j-i])%=MOD;
        }
        cir(i,1,n+1) (ans+=d[i][n])%=MOD;
    }
    cout<<ans<<'\n';
    return 0;
}
