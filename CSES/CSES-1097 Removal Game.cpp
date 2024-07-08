#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
vector<vector<lint>> D;
vector<lint> al;
lint sigment(int l,int r){return al[r]-(l?al[l-1]:0);}
lint dp(int l,int r){
    auto&d=D[l][r];
    if(d!=-1) return d;
    if(l==r) return d=sigment(l,r);
    if(l+1==r) return d=max(sigment(l,l),sigment(r,r));
    return d=sigment(l,r)-min(dp(l+1,r),dp(l,r-1));
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n;cin>>n;al.resize(n);
    for(auto&i:al) cin>>i;
    cir(i,1,n) al[i]+=al[i-1];
    D.assign(n,vector<lint>(n,-1));
    cout<<dp(0,n-1)<<'\n';
    return 0;
}