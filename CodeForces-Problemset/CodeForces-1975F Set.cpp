#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
auto divide(int s,int x,vector<int> wx,vector<int>&ans){
    if(!x) return wx[0]&1?ans.push_back(s):void();
    const auto n=1<<x;
    [&](){
        vector<int> ax;ax.reserve(n>>1);
        cir(i,0,n>>1) ax.push_back(wx[i]&wx[i+(n>>1)]);
        divide(s,x-1,ax,ans);
    }();
    [&](){
        vector<int> ax;ax.reserve(n>>1);
        cir(i,0,n>>1) ax.push_back(wx[i]&(wx[i+(n>>1)]>>1));
        divide(s|(n>>1),x-1,ax,ans);
    }();
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n;cin>>n;vector<int> a((1<<n)-1);
    for(auto&i:a) cin>>i;
    a.insert(a.begin(),1);
    vector<int> ans;
    divide(0,n,a,ans);
    cout<<ans.size()<<'\n';
    for(auto&i:ans) cout<<i<<'\n';
    return 0;
}
