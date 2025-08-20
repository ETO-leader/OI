#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
class dp{
private:
    string lim;
public:
    auto value(){
        if(lim=="0") return 0ll;
        const auto l=(int)(lim.size());
        vector<vector<array<lint,2>>> f(l,vector<array<lint,2>>(10,array<lint,2>{-1,-1}));
        auto dfs=[&](auto __self,int u,int w,int lm){
            if(u<0) return 1ll;
            if(f[u][w][lm]>-1) return f[u][w][lm];
            f[u][w][lm]=0;
            const auto ul=(lm?lim[u]-'0':9);
            cir(uw,0,ul+1) if(abs(uw-w)>1) f[u][w][lm]+=__self(__self,u-1,uw,lm&&(uw==ul));
            return f[u][w][lm];
        };
        auto ans=0ll;
        cir(i,0,l-1) cir(w,1,10) ans+=dfs(dfs,i-1,w,false);
        cir(w,1,lim[l-1]-'0') ans+=dfs(dfs,l-2,w,false);
        ans+=dfs(dfs,l-2,lim[l-1]-'0',true);
        return ans;
    }
    dp(lint v):lim(to_string(v)){reverse(lim.begin(),lim.end());}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    lint a,b;cin>>a>>b;
    cout<<dp(b).value()-dp(a-1).value()<<'\n';
    return 0;
}
