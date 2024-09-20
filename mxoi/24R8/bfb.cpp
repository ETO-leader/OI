#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
ifstream fcin("b.in");
ofstream fcout("b.ans");
class fileio{
public:
    ~fileio(){
        fcin.close();fcout.close();
    }
} use_fileio;
using lint=long long;
static constexpr auto MOD=(lint)(1e9+7);
class mathbase{
public:
    constexpr auto qpow(lint a,lint b){
        auto res=1ll;
        while(b){
            if(b&1) (res*=a)%=MOD;
            (a*=a)%=MOD;b>>=1;
        }
        return res;
    }
    constexpr auto inv(lint x){return qpow(x,MOD-2);}
    constexpr auto pref(lint x){
        return (x/2*3+(x&1)*2)%MOD;
    }
} math;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n,m;fcin>>n>>m;vector<int> b(m);
    for(auto&i:b) fcin>>i,--i;
    auto change=[&](auto x){
        cir(i,0,n) x[i]=b[x[i]];
        return x;
    };
    auto changecount=[&](auto x){
        const auto cmp=x;
        auto ans=1ll;
        x=change(x);
        while(x!=cmp) x=change(x),++ans;
        return ans;
    };
    auto dfs=[&](auto __self,basic_string<int> x)->lint {
        if((int)(x.size())==n) return changecount(x);
        auto res=0ll;
        cir(w,0,m) (res+=math.inv(m)*__self(__self,x+w))%=MOD;
        return res;
    };
    fcout<<dfs(dfs,basic_string<int>())<<'\n';
    return 0;
}
