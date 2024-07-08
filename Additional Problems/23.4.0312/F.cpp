#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
const int MOD=998244353;
using lint=long long;
using VI=vector<lint>;
VI fact;
void init_fact(int n){
    fact.resize(n+1);fact[0]=1;
    cir(i,1,n+1) fact[i]=fact[i-1]*i%MOD;
}
lint qpow(lint a,lint b){
    lint res=1;
    while(b){
        if(b&1) (res*=a)%=MOD;
        (a*=a)%=MOD;b>>=1;
    }
    return res;
}
lint inv(lint p){return qpow(p,MOD-2);}
lint C(int a,int b){
    if(a<b) return 0;
    if(a<0||b<0) return 0;
    if(!b) return 1;
    return fact[a]*inv(fact[b])%MOD*inv(fact[a-b])%MOD;
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,k;cin>>n>>k;init_fact(n);
    vector<VI> D(k+1,VI(n+1));VI v(n);
    for(auto&i:v) cin>>i;
    D[0][0]=1;
    cir(i,1,k+1) cir(j,0,n+1)
        D[i][j]=(D[i-1][j]*2*j%MOD+(j?D[i-1][j-1]:0))%MOD;
    lint ans=0;
    cir(i,0,n+1) for(int j=n-i;~j;--j){
        if(n-i-j>1&&v[n-j-2]>v[n-j-1]) break;
        (ans+=C(i+j,j)*D[k][i+j])%=MOD;
    }
    cout<<ans<<'\n';
    return 0;
}
