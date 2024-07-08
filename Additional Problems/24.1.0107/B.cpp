#include<bits/stdc++.h>
#include<modint>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using VI=vector<int>;
static constexpr int MOD=1e9+7;
using mlint=modlong<MOD>;
using arx=array<array<mlint,2>,2>;
vector<vector<arx>> D;
vector<VI> G;
auto dfs(int u,const int k,int f=0)->int{
    int res=1;auto&d=D[u];
    d[0][0][0]=d[1][0][1]=1;
    for(auto&i:G[u]) if(i!=f){
        int siz=dfs(i,k,u);
        vector<arx> nd(k+1);
        cir(x,0,min(res,k)+1){
            cir(y,0,min(siz,k-x)+1){
                nd[x+y][0][0]+=d[x][0][0]*
                    D[i][y][1][0];
                nd[x+y][1][0]+=d[x][0][0]*
                    D[i][y][1][1]+d[x][1][0]*
                    (D[i][y][1][0]+D[i][y][1][1]);
                nd[x+y][0][1]+=d[x][0][1]*(
                    D[i][y][0][0]+D[i][y][1][0]);
                nd[x+y][1][1]+=[&](){
                    auto res=d[x][0][1]*(
                        D[i][y][0][1]+D[i][y][1][1]);
                    cir(a,0,2) cir(b,0,2)
                        res+=d[x][1][1]*D[i][y][a][b];
                    return res;
                }();
            }
        }
        cir(x,0,k+1) d[x]=nd[x];
        res+=siz;
    }
    return res;
}
auto getans(int k){
    dfs(1,k);
    return D[1][k][1][0]+D[1][k][1][1];
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,k;cin>>n>>k;G.resize(n+1);
    D.resize(n+1);
    cir(i,0,n+1) D[i]=vector<arx>(k+1);
    cir(i,0,n-1){
        int u,v;cin>>u>>v;
        G[u].push_back(v);G[v].push_back(u);
    }
    cout<<getans(k)<<'\n';
    return 0;
}
