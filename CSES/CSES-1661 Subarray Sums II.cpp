#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,x;cin>>n>>x;vector<lint> v(n);
    for(auto&i:v) cin>>i;
    cir(i,1,n) v[i]+=v[i-1];
    unordered_map<lint,int> mp;mp[0]=1;
    lint ans=0;
    for(auto&i:v){
        if(mp.count(i-x)) ans+=mp[i-x];
        mp[i]++;
    }
    cout<<ans<<'\n';
    return 0;
}