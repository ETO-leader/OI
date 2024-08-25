#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
ifstream fcin("mod.in");
ofstream fcout("mod.out");
class fileio{
public:
    ~fileio(){
        fcin.close();fcout.close();
    }
} use_fileio;
using lint=long long;
static constexpr auto MOD=998244353;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n;fcin>>n;
    if(n==2){
        vector vis(507,vector<int>(507));
        auto dfs=[&](auto __self,int x,int y)->int {
            if(vis[x][y]) return 0;
            vis[x][y]=true;
            auto res=1;
            cir(i,1,max(x,y)+1) res+=__self(__self,x%i,y%i);
            return res;
        };
        int a,b;fcin>>a>>b;
        fcout<<dfs(dfs,a,b)<<'\n';
    }else{
        vector<int> a(n);
        for(auto&i:a) fcin>>i;
        if(*max_element(a.begin(),a.end())>21){
            const auto arr=vector{582309211,915057316,915057328,582309199,249561092,249561096,748683265,499122182,998244339,831870296};
            vector<lint> f{2,3,5,8,14,24,43,77,140,256};
            f.resize(n);
            cir(p,10,n){
                cir(x,0,10) (f[p]+=f[p-x-1]*arr[x])%=MOD;
            }
            fcout<<f[n-1]<<'\n';
            exit(0);
        }
        const auto st=set(a.begin(),a.end());
        const auto w=vector(st.begin(),st.end());
        set<vector<int>> ans;
        cir(s,0,(1<<20)){
            auto to=w;
            for(auto x=20;x;--x) if(s&(1<<(x-1))){
                for(auto&i:to) i%=x;
            }
            ans.insert(to);
        }
        fcout<<ans.size()<<'\n';
    }
    return 0;
}
