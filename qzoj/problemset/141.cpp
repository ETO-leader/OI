#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n;cin>>n;vector<int> a(n);
    for(auto&i:a) cin>>i;
    sort(a.begin(),a.end());
    for(auto&i:a) cout<<i<<' ';
    cout<<'\n';
    return 0;
}
