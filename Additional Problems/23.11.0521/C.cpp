#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
using VI=vector<lint>;
const lint MOD=1e9+7;
vector<VI> D,vis,cx,comb;
void initcomb(int x){
    comb.assign(x,VI(x));
    comb[0][0]=1;
    cir(i,1,x) cir(j,0,x){
        if(j) (comb[i][j]+=comb[i-1][j-1]);
        (comb[i][j]+=comb[i-1][j])%=MOD;
    }
}
lint C(int a,int b){return comb[a][b];}
pair<lint,lint> dfs(int p,int c,
    const int mxd,const int n,const lint k){
    if(p==-1) return {0LL,(!c)*1LL};
    c+=(!!(k&(1LL<<p)));
    if(c>mxd) return {0LL,0LL};    
    auto&d=D[p][c],&cc=cx[p][c];
    if(vis[p][c]) return {d,cc};
    vis[p][c]=true;
    cc=0;
    cir(i,0,min(n+1,c+1)){
        auto [dx,x]=dfs(p-1,(c-i)*2,mxd,n,k);
        (d+=(1LL*(i&1)*(1LL<<p)%MOD*x+dx)%MOD*C(n,i)%MOD)%=MOD;
        (cc+=x*C(n,i))%=MOD;
    }
    return {d,cc};
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    lint n,m;cin>>n>>m;
    initcomb(1145);
    const int l=log2(n)+2;
    D.assign(l,VI(m*2+1));
    vis.assign(l,VI(m*2+1));
    cx.assign(l,VI(m*2+1));
    cout<<dfs(l-1,0,m*2,m,n).first<<'\n';
    return 0;
}
