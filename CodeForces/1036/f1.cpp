#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto MOD=998244353;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    while(T--) []{
        int n,m;cin>>n>>m;
        vector ban(n,vector<int>(n));
        cir(i,0,m){
            int p,w;cin>>p>>w;--p;--w;
            ban[p][w]=true;
        }
        vector ok(n,vector(n+1,vector<int>(n,true)));
        cir(i,0,n) cir(s,1,n-i+1) cir(r,0,s){
            cir(c,0,s) ok[i][s][r]&=(!ban[i+c][(r+c)%s]);
        }
        vector f(n+1,vector(n,vector<lint>(2)));
        f[0][0][0]=1;
        cir(i,0,n) cir(w,0,n) cir(b,0,2) cir(s,1,n-i+1){
            if(ok[i][s][0]) (f[i+s][s-1][true]+=f[i][w][b])%=MOD;
            cir(r,1,s) if(ok[i][s][r]&&((!b)||r!=w+1)) (f[i+s][r-1][false]+=f[i][w][b])%=MOD;
        }
        auto ans=0ll;
        for(auto&x:f[n]) for(auto&w:x) (ans+=w)%=MOD;
        cout<<ans<<'\n';
    }();
    return 0;
}
