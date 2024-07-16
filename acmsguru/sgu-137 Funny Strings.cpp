#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,k;cin>>n>>k;vector a(n,k/n);
    const auto x=k%n;
    for(auto i=0;i<x&&(n*(i+1)/x)<n-1;++i) ++a[n*(i+1)/x];
    ++a[n-1];
    for(auto&i:a) cout<<i<<' ';
    cout<<'\n';
    return 0;
}
