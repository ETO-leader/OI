#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
const int MOD=1e9+7;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,m;cin>>n>>m;vector<lint> Inv(n+m,1);
    cir(i,2,n+m) Inv[i]=Inv[MOD%i]*(MOD-MOD/i)%MOD;
    lint ans=1;
    cir(i,1,n+m){
        (ans*=i)%=MOD;
        if(i<=m) (ans*=Inv[i])%=MOD;
        if(i<n) (ans*=Inv[i])%=MOD;
    }
    cout<<ans<<'\n';
    return 0;
}