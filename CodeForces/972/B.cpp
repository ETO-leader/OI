#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
static constexpr auto _inf=(int)(1e9+7);
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    while(T--) [&](){
        int n,m,q;cin>>n>>m>>q;
        vector<int> b(m);
        for(auto&i:b) cin>>i;
        b.push_back(-_inf);
        b.push_back(_inf);
        ranges::sort(b);
        cir(i,0,q){
            int p;cin>>p;
            const auto lx=*prev(ranges::lower_bound(b,p));
            const auto rx=*ranges::lower_bound(b,p);
            if(lx<0) cout<<rx-1<<'\n';
            else if(rx>_inf-1) cout<<n-lx<<'\n';
            else cout<<(rx-lx)/2<<'\n';
        }
    }();
    return 0;
}
