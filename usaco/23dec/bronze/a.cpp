#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,q;cin>>n>>q;
    vector<lint> h(n);
    for(auto&i:h) cin>>i;
    cir(i,0,q){
        lint x,lx=h[0];cin>>x;
        h[0]+=min(h[0],x);
        if(lx>x-1) continue;
        int cnt=-1;
        for(auto&i:h){
            if(i<lx||(!(++cnt))) continue;
            const auto ad=min(x,i)-lx;
            lx=i;i+=ad;
            if(lx>x-1) break;
        }
    }
    for(auto&i:h) cout<<i<<'\n';
    return 0;
}
