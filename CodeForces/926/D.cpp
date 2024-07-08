#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
using VI=vector<lint>;
static constexpr auto MOD=998244353;
class solver{
private:
    vector<VI> gr;
    VI f,fr;
    //f[u]: There're some dangerous crosses in this sub-tree,sum of methods
    auto dfs(int u,int fx=0)->void{
        f[u]=1;fr[u]=fx;
        for(auto&i:gr[u]) if(i!=fx){
            dfs(i,u);(f[u]*=(f[i]+1))%=MOD;
        }
    }
    auto getans(int u){// make this node black and certainly only 1 sub-tree has dangerous crosses
        lint cnt=0;
        for(auto&i:gr[u]) if(i!=fr[u]) (cnt+=f[i])%=MOD;
        return cnt;
    }
public:
    solver(int n):gr(n+1),f(n+1),fr(n+1){
        cir(i,0,n-1){
            int u,v;cin>>u>>v;
            gr[u].push_back(v);gr[v].push_back(u);
        }
        dfs(1);auto ans=(f[1]+1)%MOD;
        cir(i,1,n+1) (ans+=getans(i))%=MOD;
        cout<<ans<<'\n';
    }
};
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int T;cin>>T;
    while(T--) [](){
        int n;cin>>n;
        solver solve(n);
    }();
    return 0;
}
