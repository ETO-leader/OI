#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
#define cirr(i,a,b) for(int i=b-1;i>=a;--i)
using namespace std;
using VI=vector<int>;
const int _inf=1e9+7;
vector<vector<VI>> D;
vector<VI> G,g;
int findroot(int n){
    cir(i,0,n+1) if(G[i].size()>1)
        return i;
    return -1;
}
int dfs(int u,int f=0){
    auto&d=D[u];
    if(G[u].size()==1){
        d[0][0]=d[1][1]=0;
        return 1;
    }
    const int c=(D.front().size()-2);
    int cnx=0,dtag=true;
    g=d;
    for(auto&i:G[u]) if(i!=f){
        int ad=dfs(i,u);g=d;
        if(dtag){
            cir(ix,0,min(c,ad+1)){
                d[ix][0]=min(D[i][ix][0],D[i][ix][1]+1);
                d[ix][1]=min(D[i][ix][1],D[i][ix][0]+1);
            }
            cnx+=ad;
            dtag=false;continue;
        }
        cir(ix,0,min(c,cnx+1)) d[ix][0]=d[ix][1]=_inf;
        cirr(ix,0,min(cnx+1,c)) cir(jx,0,ad+1){
            if(ix+jx>c) break;
            d[ix+jx][0]=min({d[ix+jx][0],g[ix][0]+
                D[i][jx][0],g[ix][0]+D[i][jx][1]+1});
            d[ix+jx][1]=min({d[ix+jx][1],g[ix][1]+
                D[i][jx][1],g[ix][1]+D[i][jx][0]+1});
        }
        cnx+=ad;
    }
    return cnx;
}
void bad_data_type(int errcode){
    cout<<errcode<<'\n';exit(0);
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n;cin>>n;G.resize(n+1);
    D.assign(n+1,vector<VI>(n/2+7,VI(2,_inf)));
    cir(i,0,n-1){
        int u,v;cin>>u>>v;
        G[u].push_back(v);G[v].push_back(u);
    }
    int root=findroot(n);
    if(root<0) bad_data_type(1);
    int l=dfs(root);
    cout<<min(D[root][l/2][0],D[root][l/2][1])<<'\n';
    return 0;
}
