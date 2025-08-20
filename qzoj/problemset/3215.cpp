#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto MOD=(int)(1e9+7);
class dp{
private:
    vector<int> lim;
public:
    auto value(){
        const auto l=(int)(lim.size());
        vector<vector<array<lint,2>>> f(l,vector<array<lint,2>>(2,array<lint,2>{-1,-1}));
        auto dfs=[&](auto __self,int u,int w,int lm){
            if(u<0) return 1ll;
            if(f[u][w][lm]>-1) return f[u][w][lm];
            f[u][w][lm]=0;
            const auto ul=(lm?lim[u]:1);
            cir(uw,0,ul+1) if(!(w&&uw)) f[u][w][lm]+=__self(__self,u-1,uw,lm&&(uw==ul));
            return f[u][w][lm];
        };
        return dfs(dfs,(int)(lim.size())-1,0,true);
    }
    dp(lint v){
        while(v) lim.emplace_back(v&1),v>>=1;
    }
};
class matrix:public array<array<lint,2>,2>{
public:
    auto operator*(matrix b){
        auto res=matrix();
        cir(k,0,2) cir(i,0,2) cir(j,0,2){
            (res[i][j]+=(*this)[i][k]*b[k][j])%=MOD;
        }
        return res;
    }
    auto pow(auto k){
        auto res=matrix(),pw=*this;
        res[0][0]=res[1][1]=1;
        while(k){
            if(k&1) res=res*pw;
            pw=pw*pw;k>>=1;
        }
        return res;
    }
    matrix(){memset(this->begin(),0,sizeof(*this));}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    while(T--) []{
        lint n;cin>>n;
        cout<<dp(n).value()-1<<'\n';
        auto f=matrix(),w=matrix();
        f[0][0]=1;
        w[0][0]=w[0][1]=w[1][0]=1;
        f=f*w.pow(n);
        cout<<(f[0][0]+f[0][1])%MOD<<'\n';
    }();
    return 0;
}
