#include<bits/stdc++.h>
#define cir(i,a,b) for(auto i=a;i<b;++i)
using namespace std;
ifstream inf("set.in");
ofstream ouf("set.out");
using lint=long long;
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
    vector<vector<lint>> f(lgx,vector<lint>(lgx));
    f[0][0]=1;
    cir(i,0,lgx-1) cir(j,0,i+1){
        (f[i+1][j]+=f[i][j]*(j+1))%=MOD;
        (f[i+1][j+1]+=f[i][j])%=MOD;
    }
    vector<lint> sf(lgx);
    cir(i,0,lgx) sf[i]=accumulate(f[i].begin()+1,f[i].end(),0ll)%MOD;
    set<vector<int>> st;
    cir(x,1,maxn) [&]{
        auto n=x;
        auto cnt=0;
        vector<int> u;
        for(auto&x:pr) if(!(n%x)){
            ++cnt;
            auto c=0;
            while(!(n%x)) n/=x,++c;
            u.emplace_back(c);
        }
        if(n>1){
            if(isp.test(n)){
                ++cnt;
                u.emplace_back(1);
            }else{
                const auto sqr=(int)(roundl(sqrt(n)));
                if(sqr*sqr==n) ++cnt,u.emplace_back(2);
                else cnt+=2,u.emplace_back(1),u.emplace_back(1);
            }
        }
        st.emplace(u);
        if(!(x%1000000)) cerr<<x<<": "<<st.size()<<'\n';
        ouf<<sf[cnt]<<'\n';
    }();
    return 0;
}
