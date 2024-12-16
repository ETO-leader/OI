#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto _inf=(int)(1e9+7);
class tree{
private:
    vector<vector<int>> gr;
    vector<array<lint,5>> f;
    // 0: 下面无黑点
    // 1: 某个儿子为白点
    // 2: 该点为白点
    // 3: 某个儿子为黑点且无儿子为白点
    // 4: 该点为黑点
    vector<int> imp;
    auto dfs(int u,int fr=-1)->void{
        if(imp[u]){
            cir(i,0,4) f[u][i]=_inf;
            for(auto&i:gr[u]) if(i!=fr){
                dfs(i,u);
                if(imp[i]) f[u][4]+=f[i][4];
                else f[u][4]+=min(f[i][1],f[i][2]);
            }
        }else{
            array<array<array<lint,2>,2>,2> g;
            cir(i,0,2) cir(j,0,2) cir(k,0,2) g[i][j][k]=_inf;
            g[0][0][0]=0;f[u][4]=_inf;
            // 白点儿子 / 黑点儿子 / 必须填白
            for(auto&i:gr[u]) if(i!=fr){
                dfs(i,u);
                if(imp[i]) cir(x,0,2) cir(y,0,2){
                    g[x][1][y]=min({g[x][0][y],g[x][1][y]})+f[i][4];
                    g[x][0][y]=_inf;
                }else{
                    const auto gx=g;
                    cir(b,0,2) cir(y,0,2) g[1][b][y]=min(g[1][b][y]+min({f[i][0],f[i][1],f[i][2]}),g[0][b][y]+f[i][2]);
                    cir(b,0,2) cir(y,0,2) g[0][b][y]+=min({f[i][0],f[i][1],f[i][2]});
                    cir(x,0,2) cir(y,0,2) g[x][y][1]=min(g[x][y][1],min(gx[x][y][0],gx[x][y][1])+f[i][3]);
                }
                // if(u==1&&i==3) clog<<"! "<<g[1][0][0]<<'\n';
            }
            f[u][0]=g[0][0][0];
            f[u][1]=min(g[1][0][0],g[1][1][0]);
            f[u][2]=min({g[0][0][0],g[0][1][0],g[1][0][0],g[1][1][0],g[0][0][1],g[0][1][1],g[1][0][1],g[1][1][1]})+1;
            f[u][3]=g[0][1][0];
        }
        // clog<<u<<":\n";
        // cir(i,0,5) clog<<f[u][i]<<' ';
        // clog<<'\n';
    }
public:
    auto link(int u,int v){
        gr[u].push_back(v);
        gr[v].push_back(u);
    }
    auto check(vector<int> _x){
        imp=_x;dfs(0);
        return min({f[0][0],f[0][1],f[0][2],f[0][4]});
    }
    tree(int _n):gr(_n),f(_n){}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n,k;cin>>n>>k;vector<int> imp(n);
    cir(i,0,k){
        int x;cin>>x;--x;imp[x]=true;
    }
    tree gr(n);
    cir(i,0,n-1){
        int u,v;cin>>u>>v;--u;--v;
        gr.link(u,v);
    }
    cout<<gr.check(imp)<<'\n';
    return 0;
}
