#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr int MOD=998244353;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int T;cin>>T;
    while(T--){
        string s;cin>>s;
        for(auto&i:s) i-='0';
        const int n=s.size();
        vector<vector<lint>> D(n,vector<lint>(2));
        vector<vector<lint>> C(n,vector<lint>(2));
        D[0][s.front()]=0;C[0][0]=C[0][1]=1;
        D[0][s.front()^1]=1;
        cir(i,1,n){
            D[i][0]=min(((!s[i])?D[i-1][1]:MOD),
                D[i-1][0]+1);
            D[i][1]=min((s[i]?D[i-1][0]:MOD),
                D[i-1][1]+1);
            if((!s[i])&&D[i-1][1]==D[i][0])
                (C[i][0]+=C[i-1][1])%=MOD;
            if(D[i-1][0]+1==D[i][0])
                (C[i][0]+=C[i-1][0])%=MOD;
            if(s[i]&&D[i-1][0]==D[i][1])
                (C[i][1]+=C[i-1][0])%=MOD;
            if(D[i-1][1]+1==D[i][1])
                (C[i][1]+=C[i-1][1])%=MOD;
        }
        lint ans=min(D[n-1][0],D[n-1][1]);
        cout<<ans<<' '<<((ans==D[n-1][0])*
            C[n-1][0]+(ans==D[n-1][1])*
            C[n-1][1])%MOD*[&](){
                lint res=1;
                cir(i,1,ans+1) (res*=i)%=MOD;
                return res;
            }()%MOD<<'\n';
    }
    return 0;
}
