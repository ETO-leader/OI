#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
class tree{
private:
    vector<vector<pair<int,int>>> gr;
    vector<vector<lint>> uf;
    auto dfs(int u,int f=-1)->int{
        auto res=0;
        for(auto&[v,w]:gr[u]) if(v!=f){
            const auto lf=uf[u];
            const auto szi=dfs(v,u);
            uf[u].resize(res+szi+2);
            cir(i,0,res+1) cir(j,0,szi+1){
                uf[u][i+j+1]=max(uf[u][i+j+1],lf[i]+uf[v][j]+w);
            }
            res+=szi+1;
        }
        return res;
    }
public:
    auto link(int u,int v,int w){
        gr[u].emplace_back(v,w);
        gr[v].emplace_back(u,w);
    }
    auto check(const auto k){
        dfs(0);
        return uf[0][k];
    }
    tree(int _n):gr(_n),uf(_n,vector<lint>(1)){}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n,k;cin>>n>>k;
    tree gr(n);
    cir(i,0,n-1){
        int u,v,w;cin>>u>>v>>w;--u;--v;
        gr.link(u,v,w);
    }
    cout<<gr.check(k)<<'\n';
    return 0;
}
