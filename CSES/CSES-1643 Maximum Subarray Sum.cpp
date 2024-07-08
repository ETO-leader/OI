#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n;cin>>n;vector<lint> v(n),D(n);
    for(auto&i:v) cin>>i;
    D[0]=v[0];
    cir(i,1,n) D[i]=max(v[i],D[i-1]+v[i]);
    cout<<*max_element(D.begin(),D.end())<<'\n';
    return 0;
}