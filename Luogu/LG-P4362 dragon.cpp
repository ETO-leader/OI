#include<bits/extc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto _infl=(lint)(1e15l);
class tree{
private:
    vector<vector<pair<int,int>>> gr;
    vector<int> siz;
    const int k;
    auto init(int u,int f=-1)->int{
        siz[u]=1;
        for(auto&[v,w]:gr[u]) if(v!=f) siz[u]+=init(v,u);
        return siz[u];
    }
    auto dfs(int u,int f=-1)->vector<vector<lint>>{
        auto cnt=1;
        vector<vector<lint>> uf(k,vector<lint>(cnt+1,_infl));
        cir(i,0,k) uf[i][!i]=0;
        for(auto&[v,w]:gr[u]) if(v!=f){
            const auto nf=dfs(v,u);
            auto lf=uf;
            uf.clear();
            uf.resize(k,vector<lint>(cnt+siz[v]+1,_infl));
            cir(i,0,k) cir(j,0,k){
                cir(uc,0,cnt+1) cir(vc,0,siz[v]+1){
                    uf[i][uc+vc]=min(uf[i][uc+vc],lf[i][uc]+nf[j][vc]+(i==j)*w);
                }
            }
            cnt+=siz[v];
        }
        return uf;
    }
public:
    auto link(int u,int v,int w){
        gr[u].emplace_back(v,w);
        gr[v].emplace_back(u,w);
    }
    auto check(const int m){
        init(0);
        return dfs(0)[0][m];
    }
    tree(int _n,int _k):gr(_n),siz(_n),k(_k){}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n,m,k;cin>>n>>m>>k;
    tree gr(n,min(m,3));
    cir(i,0,n-1){
        int u,v,w;cin>>u>>v>>w;--u;--v;
        gr.link(u,v,w);
    }
    cout<<(m+k-1>n?-1:gr.check(k))<<'\n';
    return 0;
}
