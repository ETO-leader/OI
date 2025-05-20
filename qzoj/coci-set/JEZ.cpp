#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n,m;lint k;cin>>n>>m>>k;
    vector<vector<vector<int>>> f(25,vector<vector<int>>(2,vector<int>(2)));
    vector<vector<vector<int>>> vis(25,vector<vector<int>>(2,vector<int>(2)));
    auto split=[&](int sum){
        for(auto&c:f) for(auto&x:c) for(auto&i:x) i=false;
        for(auto&c:vis) for(auto&x:c) for(auto&i:x) i=false;
        auto dfs=[&](auto __self,int p,int ln,int lm){
            if(p<0) return 1;
            auto&fx=f[p][ln][lm];
            if(vis[p][ln][lm]) return fx;
            vis[p][ln][lm]=true;
            if(sum&(1<<p)){
                if((!ln)||(n&(1<<p))) fx+=__self(__self,p-1,ln,lm&&(!(m&(1<<p))));
                if((!lm)||(m&(1<<p))) fx+=__self(__self,p-1,ln&&(!(n&(1<<p))),lm);
                return fx;
            }else{
                return fx=__self(__self,p-1,ln&&(!(n&(1<<p))),lm&&(!(m&(1<<p))));
            }
        };
        --n;--m;
        const auto res=dfs(dfs,24,true,true);
        ++n;++m;
        return res;
    };
    auto ans=0ll;
    cir(sum,0,n+m){
        const auto cnt=min({sum+1,n+m-1-sum,n,m});
        if(k>cnt){
            ans+=split(sum);
        }else{
            auto ucnt=0;
            if(sum&1){
                cir(x,0,sum+1) if(!(x>n-1||sum-x>m-1)){
                    ans+=(!(x&(sum-x)));
                    ++ucnt;
                    if(ucnt>k-1) break;
                }
            }else cir(x,0,sum+1) if(!(x>m-1||sum-x>n-1)){
                ans+=(!(x&(sum-x)));
                ++ucnt;
                if(ucnt>k-1) break;
            }
            break;
        }
        k-=cnt;
    }
    cout<<ans<<'\n';
    return 0;
}
