#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto MOD=998244353;
constexpr auto digit10(auto x){
    auto res=0u;
    while(x) ++res,x/=10;
    return res;
}
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    while(T--) [&](){
        int n;cin>>n;vector<int> a(n);
        for(auto&i:a) cin>>i;
        vector f(2,vector(n+1,vector<lint>(11)));
        vector g(2,vector(n+1,vector<lint>(11)));
        vector<int> tp0,tp1;
        for(auto&i:a) (digit10(i)&1?tp1:tp0).push_back(i%11);
        auto cur=0;
        f[cur][0][0]=1;
        const auto cntx=(int)(tp1.size()+1)/2,cnty=(int)(tp1.size())/2;
        for(auto cnt=0;auto&i:tp1){
            cur^=1;++cnt;
            f[cur]=vector(n+1,vector<lint>(11));
            cir(w,0,n+1) cir(k,0,11){
                if(w) (f[cur][w][k]+=f[cur^1][w-1][(k+11-i)%11]*(cntx-w+1))%=MOD;
                (f[cur][w][k]+=f[cur^1][w][(k+i)%11]*(cnty-(cnt-w)+1))%=MOD;
            }
        }
        cir(w,0,11) g[0][0][w]=f[cur][cntx][w];// ,clog<<f[cur][cntx][w]<<' ';
        // clog<<'\n';
        cur=0;
        for(auto cnt=0;auto&i:tp0){
            cur^=1;++cnt;i=(11-i)%11;
            g[cur]=vector(n+1,vector<lint>(11));
            cir(w,0,n+1) cir(k,0,11){
                if(w) (g[cur][w][k]+=g[cur^1][w-1][(k+11-i)%11]*(w-1+cntx+(!(tp1.size()&1))))%=MOD;
                (g[cur][w][k]+=g[cur^1][w][(k+i)%11]*((cnt-w)-1+cnty+(tp1.size()&1)))%=MOD;
                // clog<<i<<":"<<cnt<<' '<<w<<' '<<k<<' '<<g[cur][w][k]<<'\n';
            }
        }
        auto ans=0ll;
        cir(i,0,n+1) (ans+=g[cur][i][0])%=MOD;
        println("{}",ans);
    }();
    return 0;
}
