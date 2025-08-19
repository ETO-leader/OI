#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
static constexpr auto MOD=(int)(1e5);
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n;cin>>n;string s;cin>>s;
    vector<vector<array<int64_t,2>>> f(n,vector<array<int64_t,2>>(n));
    auto value=[&](int l,int r){
        if(s[l]=='?'&&s[r]=='?') return 3;
        return (int)(
            (s[l]=='?'&&s[r]==')')||
            (s[l]=='?'&&s[r]==']')||
            (s[l]=='?'&&s[r]=='}')||
            (s[l]=='('&&s[r]=='?')||
            (s[l]=='['&&s[r]=='?')||
            (s[l]=='{'&&s[r]=='?')||
            (s[l]=='('&&s[r]==')')||
            (s[l]=='['&&s[r]==']')||
            (s[l]=='{'&&s[r]=='}')
        );
    };
    cir(i,0,n-1) f[i][i+1][0]=f[i][i+1][1]=value(i,i+1);
    for(auto len=4;len<n+1;len+=2){
        cir(l,0,n-len+1){
            const auto r=l+len-1;
            f[l][r][0]=f[l][r][1]=f[l+1][r-1][0]*value(l,r)%MOD;
            cir(p,l,r) (f[l][r][0]+=f[l][p][0]*f[p+1][r][1])%=MOD;
        }
    }
    cout<<f[0][n-1][0]<<'\n';
    return 0;
}
