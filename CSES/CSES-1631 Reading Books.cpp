#include<bits/stdc++.h>
using namespace std;
using lint=long long;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n;cin>>n;vector<lint> v(n);
    lint mx=0;
    for(auto&i:v) cin>>i,mx=max(mx,i);
    auto All=accumulate(v.begin(),v.end(),0LL);
    cout<<(All-mx<mx?mx*2:All)<<'\n';
    return 0;
}