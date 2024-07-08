#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
const int MOD=1e9+7;
auto initfact(size_t n){
    vector<lint> frc(1,1);
    cir(i,1,n+1) frc.push_back(frc.back()*i%MOD);
    return frc;
}
lint qpow(lint a,lint b){
    lint res=1;
    while(b){
        if(b&1) (res*=a)%=MOD;
        (a*=a)%=MOD;b>>=1;
    }
    return res;
}
vector<lint> fact;
lint inv(lint x){return qpow(x,MOD-2);}
lint C(lint a,lint b){
    return fact[b]*inv(fact[a])%MOD*inv(fact[b-a])%MOD;
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,k;cin>>n>>k;k=min(n-1,k);
    fact=initfact(n);
    lint cnx=0;
    cir(i,0,k+1){
        (cnx+=C(i,n)*C(i,n-1)%MOD)%=MOD;
    }
    cout<<cnx<<'\n';
    return 0;
}