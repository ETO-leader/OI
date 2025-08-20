#pragma GCC target("popcnt")
#include<bits/stdc++.h>
#include<tr2/dynamic_bitset>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using dbitset=tr2::dynamic_bitset<uint64_t>;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n,m;cin>>n>>m;
    vector<string> a(n);
    for(auto&i:a) cin>>i;
    vector<vector<int>> rg(n,vector<int>(m)),dw(n,vector<int>(m));
    cir(i,0,n) cir(j,0,m-1) rg[i][j]=(a[i][j]!=a[i][j+1]);
    cir(i,0,n-1) cir(j,0,m) dw[i][j]=(a[i][j]!=a[i+1][j]);
    // vector<vector<int>> vl(n,vector<int>(m));
    // cir(i,0,n) cir(j,0,m) vl[i][j]=rg[i][j]^dw[i][j];
    // auto ans=0;
    // cir(xl,0,n) cir(xr,xl,n) cir(yl,0,m) cir(yr,yl,m) if(xl!=xr||yl!=yr){
    //     auto vr=0;
    //     cir(i,xl,xr+1) cir(j,yl,yr+1) vr^=vl[i][j];
    //     cir(i,xl,xr+1) vr^=rg[i][yr];
    //     cir(j,yl,yr+1) vr^=dw[xr][j];
    //     ans+=vr;
    // }
    // cout<<ans<<'\n';
    // vector<dbitset> f(n,dbitset(m));
    // cir(i,0,n) cir(j,0,m) f[i].set(j,vl[i][j]);
    auto ans=0ll;
    // cir(l,0,n){
    //     dbitset dcur(m),rcur(m);
    //     cir(r,l,n){
    //         auto suf=0;
    //         for(auto i=m-1;~i;--i){
    //             suf^=rg[r][i];
    //             if(suf) rcur.flip(i);
    //         }
    //         const auto d1=dcur.count();
    //         const auto r1=rcur.count();
    //         ans+=
    //         // const auto s1=(dcur^rcur).count();
    //         // clog<<l<<' '<<r<<": "<<s1<<' '<<dcur<<' '<<rcur<<'\n';
    //         // ans+=s1*(m-s1)/2;
    //         suf=0;
    //         for(auto i=m-1;~i;--i){
    //             suf^=dw[r][i];
    //             if(dw[r][i]) dcur.flip(i);
    //         }
    //     }
    // }
    cir(l,0,n){
        vector<int> udw(m),urg(m);
        cir(r,l,n){
            auto suf=0;
            for(auto i=m-1;~i;--i) urg[i]^=(suf^=rg[r][i]);
            vector<int> cnt(2);
            cir(i,0,m){
                ++cnt[urg[i]^udw[i]];
                const auto xw=urg[i]^(i+1<m?udw[i+1]:0);
                ans+=cnt[xw^1];
            }
            suf=0;
            if(r+1<n) for(auto i=m-1;~i;--i) udw[i]^=(suf^=dw[r][i]);
        }
    }
    cout<<ans<<'\n';
    return 0;
}

