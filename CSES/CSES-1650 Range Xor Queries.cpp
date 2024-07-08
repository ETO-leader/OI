#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,q;cin>>n>>q;vector<int> x(n);
    for(auto&i:x) cin>>i;
    cir(i,1,n+1) x[i]^=x[i-1];
    cir(i,0,q){
        int l,r;cin>>l>>r;--l,--r;
        cout<<(x[r]^(l?x[l-1]:0))<<'\n';
    }
    return 0;
}