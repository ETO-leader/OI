#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
vector<int> D;
const int _inf=1e9+7;
int dp(int k){
    if(k<0) return _inf;
    auto&d=D[k];int kx=k;
    if(!k) return d=0;
    if(d!=_inf) return d;
    while(kx){
        if(kx%10) d=min(d,dp(k-kx%10)+1);
        kx/=10;
    }
    return d;
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n;cin>>n;D.resize(n+1,_inf);
    cout<<dp(n)<<'\n';
    return 0;
}