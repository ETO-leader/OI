#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto _infl=(lint)(1e18l);
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    while(T--) [&](){
        int n,m;cin>>n>>m;
        vector a(n,vector<lint>(m));
        for(auto&x:a) for(auto&i:x) cin>>i;
        vector f(m,vector<lint>(2));
        auto init=[&](int r){
            ranges::fill(f,vector(2,-_infl));
            [&](){
                auto h=0ll;
                cir(i,0,m){
                    h=h+a[r][i];
                    f[i][1]=h;
                    h=max(h,0ll);
                }
            }();
            [&](){
                auto h=0ll;
                for(auto i=m-1;~i;--i){
                    h=h+a[r][i];
                    f[i][0]=h;
                    h=max(h,0ll);
                }
            }();
        };
        auto update=[&](int r){
            const auto g=f;
            ranges::fill(f,vector(2,-_infl));
            [&](){
                vector h(2,-_infl);
                cir(i,0,m){
                    h[0]+=a[r][i];
                    h[1]+=a[r][i];
                    f[i][1]=g[i][0]+h[0];
                    f[i][1]=max(f[i][1],h[1]);
                    h[1]=max({h[1],h[0]+g[i][0],h[0]+g[i][1],g[i][1]+a[r][i]});
                    h[0]=max(h[0],a[r][i]);
                }
            }();
            [&](){
                vector h(2,-_infl);
                for(auto i=m-1;~i;--i){
                    h[0]+=a[r][i];
                    h[1]+=a[r][i];
                    f[i][0]=g[i][1]+h[0];
                    f[i][0]=max(f[i][0],h[1]);
                    h[1]=max({h[1],h[0]+g[i][0],h[0]+g[i][1],g[i][0]+a[r][i]});
                    h[0]=max(h[0],a[r][i]);
                }
            }();
        };
        init(0);
        cir(i,1,n) update(i);
        auto ans=*ranges::max_element(
            *ranges::max_element(f,[&](auto&a,auto&b){
                return *ranges::max_element(a)<*ranges::max_element(b);
            })
        );
        println("{}",ans);
    }();
    return 0;
}
