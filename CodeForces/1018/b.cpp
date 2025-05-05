#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    while(T--) [&]{
        int n,k;cin>>n>>k;vector<lint> l(n),r(n);
        for(auto&i:l) cin>>i;
        for(auto&i:r) cin>>i;
        auto check=[&](vector<lint> a,vector<lint> b){
            auto res=0ll;
            vector<lint> nxt;
            cir(i,0,n) res+=max(a[i],b[i]),nxt.emplace_back(min(a[i],b[i]));
            ranges::sort(nxt,greater<lint>());
            cir(i,0,k-1) res+=nxt[i];
            ++res;
            return res;
        };
        cout<<check(l,r)<<'\n';
    }();
    return 0;
}
