#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto maxf=100;
class mathbase{
private:
    const int p;
public:
    constexpr auto qpow(lint a,auto b) const{
        auto res=1ll;
        while(b){
            if(b&1) (res*=a)%=p;
            (a*=a)%=p;b>>=1;
        }
        return res;
    }
    constexpr auto inv(auto x) const{
        return qpow(x,p-2);
    }
    mathbase(const int _p):p(_p){}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T,p;cin>>T>>p;
    mathbase math(p);
    map<vector<int>,lint> ans;
    while(T--) [&]{
        lint n;cin>>n;
        map<int,int> cnt;
        cir(i,2,maxf) while(!(n%i)){
            ++cnt[i];n/=i;
        }
        vector<int> w;
        for(auto&[a,b]:cnt) w.emplace_back(b);
        ranges::sort(w);
        if(ans.contains(w)) return cout<<ans[w]<<'\n',void();
        vector<unordered_map<lint,lint>> f(w.size());
        auto dfs=[&](auto __self,int u,lint t){
            if(u==(int)(w.size())) return math.qpow(2,t)%p;
            if(f[u].contains(t)) return f[u][t];
            return f[u][t]=(
                __self(__self,u+1,t*(w[u]+1)%(p-1))-
                __self(__self,u+1,t*w[u]%(p-1))*2%p+p+
                __self(__self,u+1,t*(w[u]-1)%(p-1))
            )%p;
        };
        cout<<dfs(dfs,0,1)<<'\n';
    }();
    return 0;
}
