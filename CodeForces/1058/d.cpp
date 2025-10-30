#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto b=96;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    while(T--) []{
        int n;cin>>n;
        vector<lint> a(n);
        for(auto&x:a) cin>>x;
        vector f(n,vector<lint>(b,n));
        cir(i,0,n) f[i][0]=0;
        vector<pair<lint,int>> pre;
        pre.emplace_back(-1,-1);
        cir(i,0,n){
            while((!pre.empty())&&pre.back().first>a[i]-1) pre.pop_back();
            pre.emplace_back(a[i],i);
            f[i][0]=i+1;
            cir(c,1,b){
                const auto lb=ranges::lower_bound(pre,pair((a[i]+c-1)/c,-1));
                const auto p=prev(lb)->second;
                cir(x,0,b-c){
                    if(~p) f[i][c+x]=min(f[i][c+x],f[p][x]);
                    else f[i][c+x]=0;
                }
            }
        }
        auto ans=0ll;
        cir(i,0,n){
            auto las=i+1;
            cir(x,1,b) ans+=(las-f[i][x])*x,las=f[i][x];
        }
        cout<<ans<<'\n';
    }();
    return 0;
}
