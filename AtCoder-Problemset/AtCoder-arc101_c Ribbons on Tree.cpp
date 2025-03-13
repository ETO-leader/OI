#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto MOD=(int)(1e9+7);
class tree{
private:
    vector<vector<int>> gr;
    vector<vector<lint>> f;
    vector<lint> method;
    auto dfs(int u,int fr=-1)->int{
        auto siz=1;
        f[u][1]=1;
        for(auto&i:gr[u]) if(i!=fr){
            const auto vsiz=dfs(i,u);
            const auto lfu=vector(f[u].begin(),f[u].begin()+siz+1);
            fill(f[u].begin(),f[u].begin()+siz+1,0);
            cir(uw,1,siz+1) cir(vw,1,vsiz+1){
                (f[u][uw+vw]+=lfu[uw]*f[i][vw])%=MOD;
                if(!(vw&1)) (f[u][uw]+=lfu[uw]*f[i][vw]%MOD*method[vw/2]%MOD*(MOD-1))%=MOD;
            }
            siz+=vsiz;
        }
        return siz;
    }
public:
    auto link(int u,int v){
        gr[u].emplace_back(v);
        gr[v].emplace_back(u);
    }
    auto check(){
        dfs(0);
        auto res=0ll;
        cir(w,1,(int)(gr.size())+1) if(!(w&1)) (res+=f[0][w]*method[w/2])%=MOD;
        return res;
    }
    tree(int _n):gr(_n),f(_n,vector<lint>(_n+1)),method(_n+1,1){
        cir(x,1,_n+1) cir(i,1,x+1) (method[x]*=(i*2-1))%=MOD;
    }
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n;cin>>n;tree gr(n);
    cir(i,0,n-1){
        int u,v;cin>>u>>v;--u;--v;
        gr.link(u,v);
    }
    cout<<gr.check()<<'\n';
    return 0;
}
