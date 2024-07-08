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
lint inv(lint a,lint b){
    return a*qpow(b,MOD-2)%MOD;
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,m,k;cin>>n>>m>>k;
    vector<vector<lint>> D(n+1,vector<lint>(k+1)),
        vis(n+1,vector<lint>(k+1));
    function<lint(lint,lint)> dp=[&](int p,int kx){
        auto&d=D[p][kx];
        if(vis[p][kx]) return d;
        vis[p][kx]=true;
        if(p==n) return d=1;
        if(!kx) return d=0;
        cir(i,1,m+1) (d+=dp([&](){
            return p+i>n?p+i-(p+i-n)*2:p+i;
        }(),kx-1)*inv(1,m))%=MOD;
        return d;
    };
    cout<<dp(0,k)<<'\n';
    return 0;
}
