#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto MOD=998244353;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    while(T--) []{
        int m;cin>>m;
        vector<int> cur;
        auto ans=0;
        auto f=[&](int k){
            auto g=0;
            cir(i,0,(int)(cur.size())-k+1){
                auto mx=0;
                cir(x,0,k) mx=max(mx,cur[x+i]);
                g=gcd(g,mx);
            }
            return g;
        };
        auto vaild=[&](){
            set<int> res;
            cir(i,1,(int)(cur.size())+1) res.insert(f(i));
            return res.size()==cur.size();
        };
        auto dfs=[&](auto __self,const auto n)->void {
            if(cur.size()==n) return ans+=vaild(),void();
            auto cnt=0;
            cir(i,1,m+1){
                cur.push_back(i);
                __self(__self,n);
                cur.pop_back();
            }
        };
        cir(i,0,5) dfs(dfs,i+1);
        clog<<"ans = "<<ans<<'\n';
    }();
    return 0;
}
