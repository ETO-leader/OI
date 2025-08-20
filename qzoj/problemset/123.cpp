#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
auto&operator>>(istream&is,__uint128_t&w){
    w=0;
    string s;is>>s;
    for(auto&c:s) (w*=10)+=(c-'0');
    return is;
}
auto operator<<(ostream&os,__uint128_t w)->ostream&{
    if(w>9) os<<(w/10);
    return os<<(int)(w%10);
}
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n,m;cin>>n>>m;
    auto calc=[&](vector<__uint128_t> a){
        vector<vector<__uint128_t>> f(m,vector<__uint128_t>(m));
        cir(i,0,m) f[i][i]=(a[i]<<m);
        cir(len,2,m+1) cir(l,0,m-len+1){
            const auto r=l+len-1;
            f[l][r]=max(f[l+1][r]+(a[l]<<(m-len+1)),f[l][r-1]+(a[r]<<(m-len+1)));
        }
        return f[0][m-1];
    };
    auto ans=(__uint128_t)(0);
    cir(i,0,n){
        vector<__uint128_t> a(m);
        for(auto&x:a) cin>>x;
        ans+=calc(a);
    }
    cout<<ans<<'\n';
    return 0;
}
