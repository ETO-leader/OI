#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
ifstream inf("domino.in");
ofstream ouf("domino.out");
class fileio{
public:
    ~fileio(){
        inf.close();ouf.close();
    }
} use_fileio;
using lint=long long;
static constexpr auto MOD=998244353;
class matrix{
private:
    vector<vector<lint>> a;
public:
    auto&operator[](const int x){
        return a[x];
    }
    const auto&operator[](const int x) const{
        return a[x];
    }
    auto I(const auto n) const{
        auto res=matrix(n);
        cir(i,0,n) res[i][i]=1;
        return res;
    }
    auto operator*(const matrix x) const{
        const auto n=(int)(a.size());
        auto res=matrix(n);
        cir(k,0,n) cir(i,0,n) cir(j,0,n){
            (res[i][j]+=a[i][k]*x.a[k][j])%=MOD;
        }
        return res;
    }
    auto pow(auto x) const{
        auto res=I(a.size()),pw=*this;
        while(x){
            if(x&1) res=res*pw;
            pw=pw*pw;x>>=1;
        }
        return res;
    }
    matrix(auto _n):a(_n,vector<lint>(_n)){}
};
int main(){
    ios::sync_with_stdio(false),inf.tie(nullptr);
    int n,m;inf>>n>>m;
    vector g(1<<n,vector<lint>(1<<n));
    cir(i,0,(1<<n)) cir(s,0,(1<<n)){
        g[i][s]=[&]{
            if((i&s)!=i) return 0u;
            auto vis=0u;
            auto dfs=[&](auto __self,int cur)->void {
                if((vis>>cur)&1) return;
                vis|=(1<<cur);
                cir(i,1,n) if(((cur>>(i-1))&1)&&((cur>>i)&1)){
                    auto ncur=cur;
                    ncur^=((1<<(i-1))|(1<<i));
                    __self(__self,ncur);
                }
            };
            dfs(dfs,i^s);
            return vis;
        }();
    }
    unordered_map<lint,int> isvaild;
    unordered_map<lint,vector<lint>> f;
    auto getvaild=[&](auto __self,lint cur)->void {
        if(isvaild.count(cur)) return;
        isvaild.emplace(cur,-1);
        f[cur].resize(1<<n);
        cir(nxtl,0,(1<<n)) cir(p,0,(1<<n)) if(cur&(1<<p)){
            f[cur][nxtl]|=g[p][nxtl];
        }
        cir(nxtl,0,(1<<n)) if(f[cur][nxtl]) __self(__self,f[cur][nxtl]);
    };
    getvaild(getvaild,1);
    for(auto cnt=-1;auto&[a,b]:isvaild) b=++cnt;
    matrix h(isvaild.size());
    for(auto&[s,id]:isvaild) cir(nxtl,0,(1<<n)) if(f[s][nxtl]) ++h[id][isvaild[f[s][nxtl]]];
    matrix sf(isvaild.size());
    sf[0][isvaild[1]]=1;
    const auto result=(sf*h.pow(m))[0];
    auto ans=0ll;
    for(auto&[i,id]:isvaild) if(i&1) (ans+=result[id])%=MOD;
    ouf<<ans<<'\n';
    return 0;
}
