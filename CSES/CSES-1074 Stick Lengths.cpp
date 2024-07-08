#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
vector<lint> ch(vector<lint> v,bool r){
    if(r) reverse(v.begin(),v.end());
    int n=v.size();vector<lint> ret(n);
    cir(i,1,n) ret[i]=ret[i-1]+(abs(v[i]-v[i-1])*i);
    if(r) reverse(ret.begin(),ret.end());
    return ret;
}
const lint _inf=1e18+7;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n;cin>>n;vector<lint> v(n);
    for(auto&i:v) cin>>i;
    sort(v.begin(),v.end());
    auto gL=ch(v,false),gR=ch(v,true);
    lint ans=_inf;
    cir(i,0,n) ans=min(ans,gL[i]+gR[i]);
    cout<<ans<<'\n';
    return 0;
}