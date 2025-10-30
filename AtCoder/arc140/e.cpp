#include<bits/stdc++.h>
#define cir(i,a,b) for(auto i=a;i<b;++i)
using namespace std;
using lint=long long;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n,m;cin>>n>>m;
    vector<int> a(n);
    for(auto&x:a) cin>>x;
    const auto p=23;
    cir(i,0,n){
        cir(j,0,m) cout<<((i/p)*(j/p)+i+j)%p+1<<' ';
        cout<<'\n';
    }
    return 0;
}
