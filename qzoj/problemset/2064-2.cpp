#pragma GCC optimize("Ofast","unroll-loops")
#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n,m;cin>>n>>m;
    vector<vector<char>> a(n,vector<char>(m));
    for(auto&x:a) for(auto&i:x) cin>>i;
    vector<vector<int>> rg(n,vector<int>(m)),dw(n,vector<int>(m));
    cir(i,0,n) cir(j,0,m-1) rg[i][j]=(a[i][j]!=a[i][j+1]);
    cir(i,0,n-1) cir(j,0,m) dw[i][j]=(a[i][j]!=a[i+1][j]);
    auto ans=0ll;
    array<array<uint8_t,256>,256> wcnt;
    array<int,256> popcnt;
    cir(i,0,256) popcnt[i]=__builtin_popcount(i);
    cir(i,0,256) cir(j,0,256){
        vector<int> cnt(2);
        wcnt[i][j]=0;
        cir(p,0,8){
            ++cnt[(j>>p)&1];
            wcnt[i][j]+=cnt[((i>>p)&1)^1];
        }
    }
    if(m<2000){
        vector<array<uint8_t,256>> xrrg(n),xrdw(n),xrndw(n);
        cir(r,0,n){
            auto suf=0;
            for(auto i=m-1;~i;--i) xrrg[r][i/8]^=((suf^=rg[r][i])<<(i&7));
            suf=0;
            if(r+1<n) for(auto i=m-1;~i;--i) xrndw[r][i/8]^=(suf<<(i&7)),xrdw[r][i/8]^=((suf^=dw[r][i])<<(i&7));
        }
        array<uint8_t,256> uxr,xxr;
        memset(uxr.begin(),0,sizeof(uxr));
        memset(xxr.begin(),0,sizeof(xxr));
        array<int64_t,9> mcnt;
        memset(mcnt.begin(),0,sizeof(mcnt));
        const auto b=m/8+1;
        array<uint8_t,256> udw,urg,uxdw;
        cir(l,0,n){
            memset(udw.begin(),0,sizeof(udw));
            memset(urg.begin(),0,sizeof(urg));
            memset(uxdw.begin(),0,sizeof(uxdw));
            cir(r,l,n){
                cir(i,0,b) urg[i]^=xrrg[r][i];
                vector<uint32_t> cnt(2);
                cir(p,0,b) uxr[p]=urg[p]^udw[p];
                cir(p,0,b) xxr[p]=urg[p]^uxdw[p];
                cir(i,0,b-1) ans+=wcnt[xxr[i]][uxr[i]];
                cir(i,0,b-1){
                    mcnt[popcnt[xxr[i]]]+=cnt[0];
                    mcnt[8-popcnt[xxr[i]]]+=cnt[1];
                    cnt[1]+=popcnt[uxr[i]];
                    cnt[0]+=8-popcnt[uxr[i]];
                }
                cir(i,((b-1)<<3),m){
                    ++cnt[(uxr[b-1]>>(i&7))&1];
                    ans+=cnt[((xxr[b-1]>>(i&7))&1)^1];
                }
                cir(i,0,b) udw[i]^=xrdw[r][i];
                cir(i,0,b) uxdw[i]^=xrndw[r][i];
            }
        }
        cir(i,0,9) ans+=mcnt[i]*i;
        cout<<ans<<'\n';
    }else if(m<3007){
        vector<array<uint8_t,512>> xrrg(n),xrdw(n),xrndw(n);
        cir(r,0,n){
            auto suf=0;
            for(auto i=m-1;~i;--i) xrrg[r][i/8]^=((suf^=rg[r][i])<<(i&7));
            suf=0;
            if(r+1<n) for(auto i=m-1;~i;--i) xrndw[r][i/8]^=(suf<<(i&7)),xrdw[r][i/8]^=((suf^=dw[r][i])<<(i&7));
        }
        array<uint8_t,512> uxr,xxr;
        memset(uxr.begin(),0,sizeof(uxr));
        memset(xxr.begin(),0,sizeof(xxr));
        array<int64_t,9> mcnt;
        memset(mcnt.begin(),0,sizeof(mcnt));
        const auto b=m/8+1;
        array<uint8_t,512> udw,urg,uxdw;
        cir(l,0,n){
            memset(udw.begin(),0,sizeof(udw));
            memset(urg.begin(),0,sizeof(urg));
            memset(uxdw.begin(),0,sizeof(uxdw));
            cir(r,l,n){
                cir(i,0,b) urg[i]^=xrrg[r][i];
                vector<uint32_t> cnt(2);
                cir(p,0,b) uxr[p]=urg[p]^udw[p];
                cir(p,0,b) xxr[p]=urg[p]^uxdw[p];
                cir(i,0,b-1) ans+=wcnt[xxr[i]][uxr[i]];
                cir(i,0,b-1){
                    mcnt[popcnt[xxr[i]]]+=cnt[0];
                    mcnt[8-popcnt[xxr[i]]]+=cnt[1];
                    cnt[1]+=popcnt[uxr[i]];
                    cnt[0]+=8-popcnt[uxr[i]];
                }
                cir(i,((b-1)<<3),m){
                    ++cnt[(uxr[b-1]>>(i&7))&1];
                    ans+=cnt[((xxr[b-1]>>(i&7))&1)^1];
                }
                cir(i,0,b) udw[i]^=xrdw[r][i];
                cir(i,0,b) uxdw[i]^=xrndw[r][i];
            }
        }
        cir(i,0,9) ans+=mcnt[i]*i;
        cout<<ans<<'\n';
    }else{
        vector<vector<uint8_t>> xrrg(n,vector<uint8_t>(m/8+1)),xrdw(n,vector<uint8_t>(m/8+1)),xrndw(n,vector<uint8_t>(m/8+1));
        cir(r,0,n){
            auto suf=0;
            for(auto i=m-1;~i;--i) xrrg[r][i/8]^=((suf^=rg[r][i])<<(i&7));
            suf=0;
            if(r+1<n) for(auto i=m-1;~i;--i) xrndw[r][i/8]^=(suf<<(i&7)),xrdw[r][i/8]^=((suf^=dw[r][i])<<(i&7));
        }
        vector<uint8_t> uxr(m/8+1),xxr(m/8+1);
        const auto b=m/8+1;
        cir(l,0,n){
            vector<uint8_t> udw(b),urg(b),uxdw(b);
            cir(r,l,n){
                cir(i,0,b) urg[i]^=xrrg[r][i];
                vector<uint32_t> cnt(2);
                cir(p,0,b) uxr[p]=urg[p]^udw[p];
                cir(p,0,b) xxr[p]=urg[p]^uxdw[p];
                cir(i,0,b-1){
                    ans+=cnt[0]*popcnt[xxr[i]]+cnt[1]*(8-popcnt[xxr[i]])+wcnt[xxr[i]][uxr[i]];
                    cnt[1]+=popcnt[uxr[i]];
                    cnt[0]+=8-popcnt[uxr[i]];
                }
                cir(i,((b-1)<<3),m){
                    ++cnt[(uxr[b-1]>>(i&7))&1];
                    ans+=cnt[((xxr[b-1]>>(i&7))&1)^1];
                }
                cir(i,0,b) udw[i]^=xrdw[r][i];
                cir(i,0,b) uxdw[i]^=xrndw[r][i];
            }
        }
        cout<<ans<<'\n';
    }
    return 0;
}
