#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
const int MOD=998244353;
lint qpow(lint x,lint y){
    lint res=1;
    while(y){
        if(y&1) (res*=x)%=MOD;
        (x*=x)%=MOD;y>>=1;
    }
    return res;
}
lint frac(lint a,lint b){
    return a*qpow(b,MOD-2)%MOD;
}
vector<int> D,vis;
int dp(int u,const int P){
    if(u<1) return 0;
    if(vis[u]) return D[u];
    auto&d=D[u];vis[u]=true;
    return d=((dp(u-1,P)+1)*frac(100-P,100)
        +(dp(u-2,P)+1)*frac(P,100))%MOD;
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,P;cin>>n>>P;
    D.resize(n+1);vis.resize(n+1);
    cout<<dp(n,P)<<'\n';
    return 0;
}
