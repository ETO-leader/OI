#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto MOD=(int)(1e9+7);
class mathbase{
private:
    vector<lint> fct,ifct;
public:
    constexpr auto qpow(lint a,auto b) const{
        auto res=1ll;
        while(b){
            if(b&1) (res*=a)%=MOD;
            (a*=a)%=MOD;b>>=1;
        }
        return res;
    }
    constexpr auto inv(auto x) const{
        return qpow(x,MOD-2);
    }
    auto init(const auto n){
        fct.resize(n,1);
        cir(i,1,n) fct[i]=fct[i-1]*i%MOD;
        ifct=fct;
        for(auto&x:ifct) x=inv(x); 
    }
    constexpr auto C(auto a,auto b) const{
        return fct[a]*ifct[b]%MOD*ifct[a-b]%MOD;
    }
} math;
static constexpr auto maxv=2048;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n;cin>>n;
    math.init(maxv*4);
    vector f(maxv*2,vector<lint>(maxv*2));
    vector<pair<int,int>> targets;
    auto ans=0ll;
    cir(i,0,n){
        int x,y;cin>>x>>y;
        ++f[maxv-x][maxv-y];
        targets.emplace_back(maxv+x,maxv+y);
        (ans+=MOD-math.C(x*2+y*2,x*2))%=MOD;
    }
    cir(i,0,maxv*2-1) cir(j,0,maxv*2-1){
        (f[i+1][j]+=f[i][j])%=MOD;
        (f[i][j+1]+=f[i][j])%=MOD;
    }
    for(auto&[x,y]:targets) (ans+=f[x][y])%=MOD;
    cout<<ans*math.inv(2)%MOD<<'\n';
    return 0;
}
