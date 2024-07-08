#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
auto getv(vector<lint>&v){
    auto n=v.size();vector<lint> ret(n);
    cir(i,1,n) ret[i]=ret[i-1]+abs(v[i]-v[i-1])*i;
    return ret;
}
template<typename T>
ostream&operator<<(ostream&os,vector<T>&v){
    for(auto&i:v) os<<i<<' ';
    return os;
}
const lint _inf=1e18+7;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,k;cin>>n>>k;vector<lint> v(n);
    unordered_map<int,int> cnt;
    for(auto&i:v) cin>>i,cnt[i]++;
    for(auto&i:cnt) if(i.second>=k)
        return cout<<"0\n",0;
    sort(v.begin(),v.end());
    auto g1=getv(v);reverse(v.begin(),v.end());
    auto g2=getv(v);lint ans=_inf;
    reverse(g2.begin(),g2.end());
    //cout<<v<<'\n'<<g1<<'\n'<<g2<<'\n';
    cir(i,0,n){
        ans=min({ans,g1[i]+g2[i]-n+k,
        (i>k-2?g1[i]:_inf),(i<=n-k?g2[i]:_inf)});
    }
    cout<<ans<<'\n';
    return 0;
}