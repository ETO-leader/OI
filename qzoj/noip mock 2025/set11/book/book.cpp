#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
ifstream inf("book.in");
ofstream ouf("book.out");
static constexpr auto maxv=203;
static constexpr auto _inf=(int)(1e9+7);
inline const auto unroll_merge(vector<int>&a,vector<int>&b,vector<int>&r){
    cir(uw,0,maxv){
        auto vw=0;
        const auto lim=maxv-uw;
        for(;vw+8<lim;vw+=8){
            const auto tw=uw+vw;
            r[tw]=min(r[tw],a[uw]+b[vw]);
            r[tw+1]=min(r[tw+1],a[uw]+b[vw+1]);
            r[tw+2]=min(r[tw+2],a[uw]+b[vw+2]);
            r[tw+3]=min(r[tw+3],a[uw]+b[vw+3]);
            r[tw+4]=min(r[tw+4],a[uw]+b[vw+4]);
            r[tw+5]=min(r[tw+5],a[uw]+b[vw+5]);
            r[tw+6]=min(r[tw+6],a[uw]+b[vw+6]);
            r[tw+7]=min(r[tw+7],a[uw]+b[vw+7]);
        }
    }
}
int main(){
    ios::sync_with_stdio(false),inf.tie(nullptr);
    int c,T;inf>>c>>T; 
    while(T--) []{
        int n;inf>>n;
        vector<int> a(n);
        for(auto&i:a) inf>>i;
        vector<vector<vector<int>>> f(n,vector<vector<int>>(n,vector<int>(maxv,_inf)));
        cir(i,0,n) f[i][i][a[i]/2]=a[i];
        cir(r,0,n) for(auto l=r;~l;--l){
            // Type I
            if(r+1<n) cir(w,0,maxv) f[l][r+1][max(w,a[r+1])/2]=min(f[l][r+1][max(w,a[r+1])/2],f[l][r][w]+max(a[r+1]-w,0));
            // Type II
            cir(ul,0,l) unroll_merge(f[ul][l-1],f[l][r],f[ul][r]);
        }
        cir(p,0,n){
            ouf<<*min_element(f[0][p].begin(),f[0][p].end())<<' ';
        }
        ouf<<'\n';
    }();
    return 0;
}
