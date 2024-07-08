#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
const int MOD=1e9+7;
vector<lint> fct,inv,fctk;
void initfctinv(int n){
    fct.resize(n,1);inv.resize(n,1);
    fctk.resize(n,1);
    cir(i,1,n) fct[i]=fct[i-1]*i%MOD;
    cir(i,2,n) inv[i]=(MOD-MOD/i)*inv[MOD%i]%MOD;
    cir(i,2,n) (inv[i]*=inv[i-1])%=MOD;
    cir(i,1,n) fctk[i]=fctk[i-1]*(i*2-1)%MOD;
}
lint C(int a,int b){
    return fct[a]*inv[b]%MOD*inv[a-b]%MOD;
}
lint calc(lint i,lint n,lint m){
    return C(n,n-m-i)*fct[m-i]%MOD*C(m-1,i-1)
        %MOD*C(m+i,i*2)%MOD*fctk[i]%MOD;
}
lint sigma(lint n,lint m){
    lint res=0;
    cir(i,1,n-m+1) if(m+i>=i*2)
        (res+=calc(i,n,m))%=MOD;
    return res;
}
bool checkspecial(lint n,lint m){
    if(!m) return cout<<1<<'\n',true;
    if(m>n) return cout<<0<<'\n',true;
    if(m==n) return cout<<fct[n-1]*inv[2]%MOD<<'\n',true;
    return false;
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int T;cin>>T;initfctinv(114514);
    while(T--){
        lint n,m;cin>>n>>m;
        if(checkspecial(n,m)) continue;
        cout<<sigma(n,m)<<'\n';
    }
    return 0;
}
