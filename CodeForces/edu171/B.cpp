#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    while(T--) [&](){
        int n;cin>>n;vector<lint> a(n);
        for(auto&i:a) cin>>i;
        auto check=[&](vector<lint> x){
            if(x.size()&1) return numeric_limits<lint>::max();
            auto ans=1ll;
            for(auto p=1;p<(int)(x.size());p+=2) ans=max(ans,x[p]-x[p-1]);
            return ans;
        };
        auto ans=check(a);
        cir(i,0,n){
            vector<lint> x;
            cir(j,0,n) if(j!=i) x.push_back(a[j]);
            ans=min(ans,check(x));
        }
        println("{}",ans);
    }();
    return 0;
}
