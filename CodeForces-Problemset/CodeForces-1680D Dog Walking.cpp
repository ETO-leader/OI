#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
using VI=vector<lint>;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n;lint k;cin>>n>>k;
    VI a(n),c(n),p(n);
    cir(i,0,n){
        cin>>a[i];
        c[i]=(i?c[i-1]:0)+(!a[i]);
        p[i]=(i?p[i-1]:0)+a[i];
    }
    auto gcnx=[&](int l,int r){
        return c[r]-(l?c[l-1]:0);
    };
    auto gpre=[&](int l,int r){
        return p[r]-(l?p[l-1]:0);
    };
    if(abs(p.back())>c.back()*k){
        cout<<"-1\n";exit(0);
    }
    lint ans=-1;
    cir(l,0,n) cir(r,l,n){
        const auto s=gpre(l,r),cx=gcnx(l,r);
        const auto ls=p[n-1]-s,lc=c[n-1]-cx;
        ans=max({
            ans,
            min(abs(s+cx*k),abs(ls-lc*k)),
            min(abs(s-cx*k),abs(ls+lc*k))
        });
    }
    cout<<ans+1<<'\n';
    return 0;
}
