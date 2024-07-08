#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using VI=vector<int>;
const int MOD=1e9+7;
const int mxn=1e5+7;
array<array<array<array<int,2>,2>,107>,mxn> D;
array<array<array<int,2>,2>,107> nd;
vector<VI> G;
void add(auto&x,auto w){(x+=(w%MOD))%=MOD;}
int dfs(int u,const int k,int f=0){
    auto&d=D[u];int res=1;
    d[0][0][0]=d[1][0][1]=1;
    for(auto&v:G[u]) if(v!=f){
        int sz=dfs(v,k,u);
        cir(i,0,min(k,res)+1) cir(j,0,min(k-i+1,sz+1)){
            add(nd[i+j][0][0],1LL*d[i][0][0]*D[v][j][1][0]);
            add(nd[i+j][1][0],1LL*d[i][0][0]*D[v][j][1][1]);
            add(nd[i+j][1][0],1LL*d[i][1][0]*
                (D[v][j][1][0]+D[v][j][1][1]));
            add(nd[i+j][0][1],1LL*d[i][0][1]*
                (D[v][j][0][0]+D[v][j][1][0]));
            add(nd[i+j][1][1],1LL*d[i][0][1]*
                (D[v][j][0][1]+D[v][j][1][1]));
            auto sum=0LL;
            cir(x,0,2) cir(y,0,2) add(sum,D[v][j][x][y]);
            add(nd[i+j][1][1],1LL*d[i][1][1]*sum);
        }
        d=nd;
        for(auto&i:nd) for(auto&j:i) for(auto&w:j) w=0;
        res+=sz;
    }
    return res;
}
int getans(int k){
    dfs(1,k);
    return (D[1][k][1][0]+D[1][k][1][1])%MOD;
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,k;cin>>n>>k;G.resize(n+1);
    cir(i,0,n-1){
        int u,v;cin>>u>>v;
        G[u].push_back(v);G[v].push_back(u);
    }
    cout<<getans(k)<<'\n';
    return 0;
}