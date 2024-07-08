#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
using VI=vector<int>;
const int MOD=998244353;
const int aimax=2e5+7;
vector<lint> fact;
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
    if((!a)||(!b)) return 1;
    return fact[a]*inv(fact[b])%MOD*inv(fact[a-b])%MOD;
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,k;cin>>n>>k;VI v(n),D(aimax<<1);
    unordered_set<int> usx;
    for(auto&i:v) cin>>i,usx.insert(i);
    init_fact(1919810);
    cir(i,0,(aimax<<1)) D[i]=(i?D[i-1]:0)+(!usx.count(i));
    lint ans=0;
    cir(i,0,(aimax<<1)) if(D[i]<=k){
        (ans+=C(k-D[i]+i-usx.count(i),i))%=MOD;
    }
    cout<<ans<<'\n';
    return 0;
}
