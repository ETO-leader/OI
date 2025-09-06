#pragma GCC optimize("unroll-loops")
#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n;cin>>n;
    vector<pair<int,int>> a(n);
    for(auto&[x,y]:a) cin>>x>>y;
    sort(a.begin(),a.end());
    vector<int> uy(n);
    cir(i,0,n) uy[i]=a[i].second;
    vector<int> ans(n);
    cir(i,0,n){
        auto cnt=0;
        ++uy[i];
        cir(j,0,i) cnt+=uy[j]<uy[i];
        --uy[i];
        ++ans[cnt];
    }
    for(auto&i:ans) cout<<i<<'\n';
    return 0;
}
