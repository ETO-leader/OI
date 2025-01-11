#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
ifstream fcin("anti.in");
ofstream fcout("anti.out");
class fileio{
public:
    ~fileio(){
        fcin.close();fcout.close();
    }
} use_fileio;
using lint=long long;
static constexpr auto MOD=998244353;
class mathbase{
public:
    constexpr auto qpow(lint a,auto b){
        auto res=1ll;
        while(b){
            if(b&1) (res*=a)%=MOD;
            (a*=a)%=MOD;b>>=1;
        }
        return res;
    }
    constexpr auto inv(auto x){return qpow(x,MOD-2);}
} math;
int main(){
    ios::sync_with_stdio(false),fcin.tie(nullptr);
    int T;fcin>>T;
    while(T--) [](){
        int n;fcin>>n;
        string s;fcin>>s;
        unordered_set<string> vis;
        auto dfs=[&](auto __self,string cur)->lint {
            if(vis.count(cur)) return 0ll;
            vis.emplace(cur);
            auto res=1ll;
            cir(i,0,(int)(cur.size())-1) if(!(cur[i]=='('&&cur[i+1]==')')){
                auto ncur=cur;
                ncur.erase(ncur.begin()+i);
                ncur.erase(ncur.begin()+i);
                (res+=__self(__self,ncur))%=MOD;
            }
            return res;
        };
        fcout<<dfs(dfs,s)<<'\n';
    }();
    return 0;
}
