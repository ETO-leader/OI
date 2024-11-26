#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto MOD=10007;
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
} math;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    lint a,b,k,n,m;cin>>a>>b>>k>>n>>m;
    // (ax+by)^k
    vector c(k+1,vector<lint>(k+1));
    c[0][0]=1;
    cir(i,1,k+1) cir(j,0,k+1){
        c[i][j]=c[i-1][j];
        if(j) (c[i][j]+=c[i-1][j-1])%=MOD;
    }
    cout<<math.qpow(a,n)*math.qpow(b,m)%MOD*c[k][n]%MOD<<'\n';
    return 0;
}
