#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using intset=bitset<32>;
const int _inf=1e9+7;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,k;cin>>n>>k;vector<intset> v(n);
    char x;
    for(auto&i:v) cir(j,0,k) cin>>x,i[j]=bool(x-'0');
    size_t ans=_inf;
    cir(i,0,n) cir(j,i+1,n)
        ans=min(ans,(v[i]^v[j]).count());
    cout<<ans<<'\n';
    return 0;
}