//CodeForces 1227G
#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n;cin>>n;vector<int> a(n);
    for(auto&i:a) cin>>i;
    vector<int> pos(n);
    iota(pos.begin(),pos.end(),0);
    sort(pos.begin(),pos.end(),[&](auto u,auto v){
        return a[u]>a[v];
    });
    vector<vector<int>> ans(n+1,vector<int>(n));
    auto c=0;
    for(auto&i:pos){
        auto p=c++;
        cir(x,0,a[i]) ans[(++p)%=(n+1)][i]=true;
    }
    cout<<n+1<<'\n';
    for(auto&i:ans){
        for(auto&j:i) cout<<j;
        cout<<'\n';
    }
    return 0;
}
