#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto MOD=998244353;
class mathbase{
public:
    constexpr auto qpow(lint a,auto b){
        auto res=1ll;
        while(b){
            if(b&1) (res*=a)%=MOD;
            (a*=a)%=MOD;b>>=1;
        }
        return res;
    }
    constexpr auto inv(lint x){return qpow(x,MOD-2);}
} math;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n;lint p;cin>>n>>p;
    (p*=math.inv(10000))%=MOD;
    vector c(n+7,vector<lint>(n+7));
    c[0][0]=1;
    cir(i,1,n+7){
        cir(j,0,n+7){
            c[i][j]=c[i-1][j];
            if(j) (c[i][j]+=c[i-1][j-1])%=MOD;
        }
    }
    vector uf(n+7,vector<lint>(n+7,-1));
    vector ug(n+7,vector<lint>(n+7,-1));
    function<lint(int,int)> f,g;
    g=[&](int n,int m){
        if(!n) return 1ll;
        if(ug[n][m]>-1) return ug[n][m];
        auto&res=ug[n][m];
        res=0;
        cir(i,0,n+1) (res+=c[n][i]*f(i,m)%MOD*f(n-i,m))%=MOD;
        return res;
    };
    f=[&](int n,int m){
        if(m<0) return 0ll;
        if(!n) return 1ll;
        if(uf[n][m]>-1) return uf[n][m];
        auto&res=uf[n][m];
        res=0;
        cir(i,0,n){
            (res+=c[n-1][i]*((f(i,m+1)*p+f(i,m-1)*(MOD+1-p))%MOD)%MOD*g(n-i-1,m))%=MOD;
        }
        return res;
    };
    auto ans=f(n,0);
    cir(i,0,n) (ans*=math.inv(i*2+1))%=MOD;
    println("{}",ans);
    return 0;
}
