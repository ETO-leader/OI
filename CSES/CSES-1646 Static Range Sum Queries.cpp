#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,q;cin>>n>>q;vector<lint> v(n);
    for(auto&i:v) cin>>i;
    cir(i,1,n) v[i]+=v[i-1];
    cir(i,0,q){
        int l,r;cin>>l>>r;--l,--r;
        cout<<v[r]-(l?v[l-1]:0)<<'\n';
    }
    return 0;
}