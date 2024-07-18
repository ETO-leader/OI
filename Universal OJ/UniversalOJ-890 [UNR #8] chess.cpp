#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto MOD=998244353;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,k;cin>>n>>k;
    string s;cin>>s;
    vector f(n,vector<lint>(k+1));
    f[0][0]=(s[0]!='1');f[0][k]=(s[0]!='0');
    cir(i,1,n) cir(x,0,k+1){
        (f[i][max(x-1,0)]+=f[i-1][x]*(s[i]!='1'))%=MOD;
        (f[i][min(x+1,k)]+=f[i-1][x]*(s[i]!='0'))%=MOD;
    }
    ranges::reverse(f);
    ranges::reverse(s);
    auto pre=1ll,ans=0ll;
    cir(i,0,n){
        if(i<n-1) (ans+=(f[i+1][0]*(s[i]!='1')+f[i+1][k]*(s[i]!='0'))*pre)%=MOD;
        if(s[i]=='?') (pre*=2)%=MOD;
    }
    cout<<(ans+pre)%MOD<<'\n';
    return 0;
}
