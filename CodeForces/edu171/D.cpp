#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto _infl=(lint)(1e18l);
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T=1;
    while(T--) [&](){
        int n;cin>>n;vector<lint> a(n);
        for(auto&i:a) cin>>i;
        auto pre=a;
        cir(i,1,n) pre[i]+=pre[i-1];
        auto ppre=pre;
        cir(i,1,n) ppre[i]+=ppre[i-1];
        vector<lint> pos;
        auto prex=0ll;
        cir(i,0,n) pos.push_back(prex),prex+=n-i;
        pos.push_back(prex);
        auto sum=[&](auto s,int l,int r){
            return ppre[r]-(l?ppre[l-1]:0)-(s?pre[s-1]:0)*(r-l+1);
        };
        vector<lint> blci(n);
        cir(i,0,n) blci[i]=sum(i,i,n-1);
        cir(i,1,n) blci[i]+=blci[i-1];
        int q;cin>>q;
        cir(i,0,q){
            lint l,r;cin>>l>>r;--l;--r;
            const auto bl=ranges::upper_bound(pos,l)-pos.begin()-1;
            const auto br=ranges::upper_bound(pos,r)-pos.begin()-1;
            // clog<<l<<' '<<r<<' '<<bl<<' '<<br<<' '<<q<<'\n';
            if(bl==br) println("{}",sum(bl,l-pos[bl]+bl,r-pos[br]+br));
            else println("{}",sum(bl,l-pos[bl]+bl,n-1)+sum(br,br,r-pos[br]+br)+blci[br-1]-blci[bl]);
        }
    }();
    return 0;
}
