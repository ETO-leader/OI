#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto _infl=(lint)(1e15l);
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n,r;cin>>n>>r;
    vector<int> a(n);
    for(auto&i:a) cin>>i;
    vector<vector<lint>> f(n+1,vector<lint>(n-1,-_infl));
    cir(i,0,n-1) f[0][i]=0;
    cir(i,1,n+1) cir(w,0,n-1) cir(lw,0,n-1){
        f[i][w]=max(f[i][w],f[i-1][lw]-a[(min(w,lw)-i*r%n+n)%n]+a[(max(w,lw)+1-i*r%n+n)%n]);
        // clog<<i<<' '<<w<<": "<<f[i][w]<<'\n';
    }
    cout<<*max_element(f[n].begin(),f[n].end())<<'\n';
    return 0;
}
