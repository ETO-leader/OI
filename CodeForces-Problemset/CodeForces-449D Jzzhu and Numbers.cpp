#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
using VI=vector<lint>;
constexpr int MOD=1e9+7;
static constexpr int upx=21;
lint qpow(lint a,lint b){
    lint res=1;
    while(b){
        if(b&1) (res*=a)%=MOD;
        (a*=a)%=MOD;b>>=1;
    }
    return res;
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n;cin>>n;VI D(1<<upx);
    cir(c,0,n){
        int x;cin>>x;++D[x];
    }
    cir(i,0,upx) cir(s,0,(1<<upx)) if(s&(1<<i))
        (D[s-(1<<i)]+=D[s])%=MOD;
    lint ans=0;
    cir(s,0,(1<<upx)){
        (ans+=((__builtin_popcount(s)&1)?
            -1:1)*(qpow(2,D[s])-1))%=MOD;
    }
    cout<<(ans+MOD)%MOD<<'\n';
    return 0;
}