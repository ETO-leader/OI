#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
using VI=vector<lint>;
const int MOD=1e9+7;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,k,q;cin>>n>>k>>q;VI v(n);
    vector<VI> D(n,VI(k+1,1));
    for(auto&i:v) cin>>i;
    cir(j,1,k+1) cir(i,0,n){
        D[i][j]=((i?D[i-1][j-1]:0)+
            (i<n-1?D[i+1][j-1]:0))%MOD;
    }
    auto C=D;
    cir(i,0,n) cir(j,0,k+1) (D[i][j]*=C[i][k-j])%=MOD;
    VI cnx(n);lint ans=0;
    cir(i,0,n) cnx[i]=accumulate(D[i].begin(),D[i].end(),
        0,[](int a,int b){return (a+b)%MOD;});
    cir(i,0,n) (ans+=(1LL*v[i]*cnx[i]))%=MOD;
    cir(i,0,q){
        int p,w;cin>>p>>w;--p;
        ((ans-=(v[p]*cnx[p]%MOD))+=MOD)%=MOD;
        v[p]=w;
        cout<<((ans+=(w*cnx[p]%MOD))%=MOD)<<'\n';
    }
    return 0;
}
