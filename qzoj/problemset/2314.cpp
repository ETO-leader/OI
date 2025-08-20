#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto MOD=(int)(1e9+7);
class acam{
private:
    static constexpr auto alpha=10;
    vector<array<int,alpha>> ch,gfail;
    vector<int> fail;
    int cnt;
public:
    auto emplace(string s){
        auto u=0;
        for(auto&x:s){
            if(!ch[u][x-'0']) ch[u][x-'0']=++cnt;
            u=ch[u][x-'0'];
        }
        return u;
    }
    auto init(){
        queue<int> q;q.emplace(0);
        while(!q.empty()){
            const auto u=q.front();q.pop();
            cir(c,0,alpha) if(ch[u][c]){
                auto ux=fail[u];
                while(ux&&(!ch[ux][c])) ux=fail[ux];
                if(u) fail[ch[u][c]]=ch[ux][c];
                q.emplace(ch[u][c]);
            }
        }
        return cnt+1;
    }
    auto move(int u,char c){
        if((!u)||ch[u][c]) return ch[u][c];
        if(gfail[u][c]>-1) return gfail[u][c];
        return gfail[u][c]=move(fail[u],c);
    }
    acam(int _n):ch(_n+7),fail(_n+7),cnt(0),gfail(_n+7,[]{
        array<int,alpha> res;
        fill(res.begin(),res.end(),-1);
        return res;
    }()){}
};
class dp{
private:
    string lim;
public:
    auto value(acam&ac,const int c,unordered_set<int> ban){
        const auto l=(int)(lim.size());
        vector<vector<array<lint,2>>> f(l,vector<array<lint,2>>(c,array<lint,2>{-1,-1}));
        auto dfs=[&](auto __self,int u,int p,int lm){
            if(u<0) return 1ll;
            if(f[u][p][lm]>-1) return f[u][p][lm];
            f[u][p][lm]=0;
            const auto ul=(lm?lim[u]-'0':9);
            cir(uw,0,ul+1) if(!ban.count(ac.move(p,uw))) (f[u][p][lm]+=__self(__self,u-1,ac.move(p,uw),lm&&(uw==ul)))%=MOD;
            return f[u][p][lm];
        };
        auto ans=0ll;
        cir(i,0,l-1) cir(w,1,10) if(!ban.count(ac.move(0,w))) ans+=dfs(dfs,i-1,ac.move(0,w),false);
        cir(w,1,lim[l-1]-'0') if(!ban.count(ac.move(0,w))) ans+=dfs(dfs,l-2,ac.move(0,w),false);
        if(!ban.count(ac.move(0,lim[l-1]-'0'))) ans+=dfs(dfs,l-2,ac.move(0,lim[l-1]-'0'),true);
        return ans%MOD;
    }
    dp(auto x):lim(x){reverse(lim.begin(),lim.end());}
};
static constexpr auto maxc=1507;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    string n;cin>>n;
    int c;cin>>c;
    acam ac(maxc);
    unordered_set<int> ban;
    cir(i,0,c){
        string s;cin>>s;
        ban.emplace(ac.emplace(s));
    }
    const auto vc=ac.init();
    cout<<dp(n).value(ac,vc,ban)<<'\n';
    return 0;
}
