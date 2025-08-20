#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
unordered_map<string,lint> uf;
class dp{
private:
    string lim;
public:
    auto value(){
        if(uf.count(lim)) return uf[lim];
        const auto l=(int)(lim.size());
        vector<array<lint,2>> f(l,array<lint,2>{-1,-1});
        auto dfs=[&](auto __self,int u,int lm){
            if(u<0) return 1ll;
            if(f[u][lm]>-1) return f[u][lm];
            f[u][lm]=0;
            const auto ul=(lm?lim[u]-'0':10);
            cir(uw,(u==(int)(lim.size())-1),ul+1) if(set<int>{0,1,8}.count(uw)) f[u][lm]+=__self(__self,u-1,lm&&(uw==ul));
            return uf[lim]=f[u][lm];
        };
        return dfs(dfs,(int)(lim.size())-1,true);
    }
    dp(auto v):lim(v){reverse(lim.begin(),lim.end());}
};
auto operator*(string s,int c){
    auto res=(string)("");
    cir(i,0,c) res+=s;
    return res;
}
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    while(T--) []{
        string l,r;cin>>l>>r;
        auto dec=[&](string s){
            auto p=prev(s.end());
            while(*p=='0') *p='9',--p;
            *p-=1;
            return s;
        };
        auto check=[&](string n){
            while(n.size()>1&&n.front()=='0') n.erase(n.begin());
            if(n=="0") return 1ll;
            const auto szn=(int)(n.size());
            auto res=1ll;
            cir(i,1,szn) res+=dp((string)("9")*((i+1)/2)).value();
            auto lp=szn/2-(!(szn&1)),rp=szn/2;
            auto ok=true;
            cir(i,0,lp+1) ok&=(set<int>{0,1,8}.count(n[i]-'0'));
            while(~lp){
                if(n[rp]>n[lp]) break;
                if(n[lp]>n[rp]) ok=false;
                --lp;++rp;
            }
            res+=ok;
            const auto v=dec(string(n.begin(),n.begin()+szn/2-(!(szn&1))+1));
            res+=dp(v).value();
            return res;
        };
        cout<<check(r)-(l!="0"?check(dec(l)):0)<<'\n';
    }();
    return 0;
}
