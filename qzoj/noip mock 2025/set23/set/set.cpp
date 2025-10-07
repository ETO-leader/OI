#include<bits/stdc++.h>
#define cir(i,a,b) for(auto i=a;i<b;++i)
using namespace std;
ifstream inf("set.in");
ofstream ouf("set.out");
using lint=long long;
static constexpr auto c=251ull;
static constexpr auto MOD=998244353;
static constexpr auto lgx=30;
static constexpr auto maxn=(int)(1e8+7);
int main(){
    ios::sync_with_stdio(false),inf.tie(nullptr);
    int T;inf>>T;bitset<maxn> isp;
    isp.set();
    vector<int> pr;
    cir(i,2,maxn) if(isp.test(i)){
        if(i<500) pr.emplace_back(i);
        for(auto j=(lint)(i)*i;j<maxn;j+=i) isp.reset(j);
    }
    unordered_map<uint64_t,lint> f;
    auto emplace=[&](vector<lint> cur){
        vector<vector<lint>> uf(cur.size()+1,vector<lint>(cur.size()+1));
        uf[0][0]=1;
        cir(i,0,(int)(cur.size())) cir(j,0,i+1){
            (uf[i+1][j]+=uf[i][j]*(cur[i]*j+1))%=MOD;
            (uf[i+1][j+1]+=uf[i][j]*cur[i])%=MOD;
        }
        auto h=(uint64_t)(0);
        for(auto&x:cur) (h*=c)+=x;
        f[h]=accumulate(uf[cur.size()].begin()+1,uf[cur.size()].end(),0ll)%MOD;
    };
    auto dfs=[&](auto __self,lint w,vector<lint> cur,int v,int c)->void {
        emplace(cur);
        cir(i,1,c+1){
            w*=v;
            if(w>maxn) break;
            cur.emplace_back(i);
            __self(__self,w,cur,v+1,i);
            cur.pop_back();
        }
    };
    dfs(dfs,1ll,{},2,lgx);
    vector<int> u;
    while(T--) [&]{
        int n;inf>>n;
        u.clear();
        for(auto&x:pr) if(!(n%x)){
            auto uc=0;
            while(!(n%x)) n/=x,++uc;
            u.emplace_back(uc);
        }
        if(n>1){
            if(isp.test(n)){
                u.emplace_back(1);
            }else{
                const auto sqr=(int)(roundl(sqrt(n)));
                if(sqr*sqr==n) u.emplace_back(2);
                else u.emplace_back(1),u.emplace_back(1);
            }
        }
        sort(u.begin(),u.end(),greater<>());
        auto h=(uint64_t)(0);
        for(auto&v:u) (h*=c)+=v;
        ouf<<f[h]<<'\n';
    }();
    return 0;
}
