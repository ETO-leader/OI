#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr int MOD=1e9+7;
constexpr auto qpow(lint a,lint b){
    auto res=1ll;
    while(b){
        if(b&1) (res*=a)%=MOD;
        (a*=a)%=MOD;b>>=1;
    }
    return res;
}
constexpr auto inv(lint x){
    return qpow(x,MOD-2);
}
constexpr auto pow2(lint x){return x*x;}
constexpr auto sum(lint l,lint r){
    return (l<r+1?(l+r)*(r-l+1)/2%MOD:0ll);
}
auto lagrange(vector<lint>&k,vector<vector<lint>>&invm,lint x){
    auto res=0ll;
    cir(xi,1,(int)(k.size())+1){
        auto ansi=k[xi-1];
        cir(xj,1,(int)(k.size())+1) if(xi!=xj){
            (ansi*=(MOD+x-xj)%MOD*invm[xi][xj]%MOD)%=MOD;
        }
        (res+=ansi)%=MOD;
    }
    return res;
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    lint n;cin>>n;
    auto contrib=[n](lint x){
        x%=MOD;
        const auto mn=n%MOD;
        return (mn+1)*(mn+x)%MOD*(mn-x+1)%MOD*inv(2)%MOD
            +MOD-mn*(mn+1)%MOD*(mn*2+1)%MOD*inv(6)%MOD
            +(x-1)*x%MOD*(x*2-1)%MOD*inv(6)%MOD;
    };
    vector<vector<lint>> invm(9,vector<lint>(9));
    cir(i,0,9) cir(j,0,9) invm[i][j]=inv((MOD+i-j)%MOD);
    auto ans=0ll;
    for(auto x=0ll;x*x<n+1;++x){
        const auto loc=(int)(sqrtl(n-pow2(x)));
        auto ad=contrib(pow2(x))%MOD;
        vector<lint> val(8);
        cir(i,1,9){
            (val[i-1]=(i-1?val[i-2]:0ll)+
                contrib(pow2(x)+pow2(i)))%=MOD;
        }
        (ad+=lagrange(val,invm,loc)*2)%=MOD;
        (ans+=ad*((bool)(x)+1))%=MOD;
    }
    cout<<ans<<'\n';
    return 0;
}
