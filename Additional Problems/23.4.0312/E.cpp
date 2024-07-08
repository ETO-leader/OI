#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
const int MOD=998244353;
vector<vector<int>> G;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,m,k,step=0;cin>>n>>m>>k;
    G.resize(n+1);
    vector<vector<int>> D(2,vector<int>(n+1));
    cir(i,0,m){
        int u,v;cin>>u>>v;
        G[u].push_back(v);G[v].push_back(u);
    }
    cir(i,1,n+1) G[i].push_back(i);
    D[step][1]=1;int ald=1;
    cir(i,0,k){
        step^=1;
        cir(j,1,n+1){
            D[step][j]=ald;
            for(auto&f:G[j])
                ((D[step][j]+=MOD)-=D[step^1][f])%=MOD;
        }
        ald=0;
        cir(j,1,n+1) (ald+=D[step][j])%=MOD;
    }
    cout<<D[step][1]<<'\n';
    return 0;
}
