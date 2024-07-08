#pragma GCC target("popcnt")
#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using bitline=bitset<3007>;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n;cin>>n;vector<bitline> vb(n);
    for(auto&i:vb) cin>>i;
    long long ans=0;
    cir(i,0,n) cir(j,i+1,n){
        auto ax=(vb[i]&vb[j]).count();
        ans+=(ax*(ax-1))/2;
    }
    cout<<ans<<'\n';
    return 0;
}