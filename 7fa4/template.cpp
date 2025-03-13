#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
class hash_128{
public:
    auto operator()(const __uint128_t x) const{
        return x&(uint64_t)(-1);
    }
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int c,T;cin>>c>>T;
    while(T--) []{
        int n,m;cin>>n>>m;
        vector<int> a(n);
        for(auto&i:a) cin>>i;
        unordered_set<__uint128_t,hash_128> vis;
        auto hash_vec=[&](vector<int>&x){
            auto res=(__uint128_t)(0);
            for(auto&i:x) (res*=71)+=i;
            return res;
        };
        auto dfs=[&](auto __self,vector<int> cur){
            if(cur.empty()) return 0;
            const auto w=hash_vec(cur);
            if(vis.count(w)) return 0;
            vis.emplace(w);
            auto pre=-1;
            auto res=1;
            cir(i,0,(int)(cur.size())) if(cur[i]>pre){
                pre=cur[i];
                auto emp=vector<int>(cur.begin()+i+1,cur.end());
                if(cur[i]-1) emp.emplace_back(cur[i]-1);
                res+=__self(__self,emp);
            }
            return res;
        };
        cout<<dfs(dfs,a)<<'\n';
    }();
    return 0;
}
