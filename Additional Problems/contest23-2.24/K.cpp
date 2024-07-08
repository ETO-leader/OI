#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto MOD=998244353;
constexpr auto qpow(lint a,lint b){
    lint res=1;
    while(b){
        if(b&1) (res*=a)%=MOD;
        (a*=a)%=MOD;b>>=1;
    }
    return res;
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n;cin>>n;vector<int> a(n);
    for(auto&i:a) cin>>i;
    vector<vector<lint>> f(n,vector<lint>(n+1));
    f[0][0]=1;
    cir(i,0,n-1) cir(w,0,i+1){
        const auto ax=w,bx=n+1-(i-w);
        if(!a[i]){
            (f[i+1][w]+=f[i][w])%=MOD;
            (f[i+1][w+1]+=f[i][w])%=MOD;
        }else{
            if(ax+1==a[i]) (f[i+1][w+1]+=f[i][w])%=MOD;
            if(bx-1==a[i]) (f[i+1][w]+=f[i][w])%=MOD;
        }
    }
    lint ans=0;
    cir(w,1,n+1) if((!a[n-1])||(a[n-1]==w)){
        (ans+=f[n-1][w-1])%=MOD;
    }
    cout<<ans<<'\n';
    return 0;
}
