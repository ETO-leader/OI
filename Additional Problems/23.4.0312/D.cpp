#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
const int MOD=1e9+7;
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
    if(b<a) return 0;
    if(a<0||b<0) return 0;
    if(!a) return 1;
    return fact[b]*inv(fact[a])%MOD*inv(fact[b-a])%MOD;
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,k;cin>>n>>k;init_fact(n);
    if(k==1){
        cout<<0<<'\n';exit(0);
    }
    vector<lint> v(n);
    for(auto&i:v) cin>>i;
    sort(v.begin(),v.end(),greater<lint>());
    lint cnt1=0,cnt2=0;
    cir(i,0,n) (cnt1+=v[i]*C(k-1,n-i-1)%MOD+MOD)%=MOD;
    reverse(v.begin(),v.end());
    cir(i,0,n) (cnt2+=v[i]*C(k-1,n-i-1)%MOD+MOD)%=MOD;
    cout<<(cnt1+MOD-cnt2)%MOD<<'\n';
    return 0;
}
