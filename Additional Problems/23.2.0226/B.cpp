#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
const lint MOD=998244353;
lint qpow(lint x,lint y,const lint P){
    lint res=1;x%=P;
    while(y){
        if(y&1) (res*=x)%=P;
        (x*=x)%=P;y>>=1;
    }
    return res;
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    lint n,k,m;cin>>n>>k>>m;
    if((!(m%MOD))&&(!qpow(k,n,MOD-1)))
        cout<<0<<'\n';
    else
        cout<<qpow(m,qpow(k,n,MOD-1),MOD)<<'\n';
    return 0;
}
