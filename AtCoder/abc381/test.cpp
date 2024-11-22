#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    vector<lint> a(10000000);
    a[0]=2;a[1]=1;
    cir(i,2,10000000) a[i]=(a[i-1]+a[i-2])%998244353;
    auto prod=1ll;
    for(auto&i:a) cout<<((prod*=i)%=998244353)<<' ';
    cout<<'\n';
    return 0;
}
