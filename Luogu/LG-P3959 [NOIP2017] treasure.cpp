#include<bits/stdc++.h>
#define cir(i,a,b) for(auto i=a;i<b;++i)
using namespace std;
using lint=long long;
using VI=vector<lint>;
const lint _inf=1e15+7;
void assign(vector<VI>&v,int f,int s,lint w=0){
    v.assign(f,VI(s,w));
}
void init(vector<VI>&W,vector<VI>&C,int _sz,int n){
    cir(i,0,_sz) cir(j,0,_sz){
        if(j&&((i&j)!=j||i==j)) continue;
        W[i][j]=0;
        cir(k,0,n) if((1<<k)&(i^j)){
            lint cnt=_inf;
            cir(x,0,n) if((1<<x)&j)
                cnt=min(cnt,C[k][x]);
            W[i][j]+=cnt;
        }
    }
}
void initD(vector<VI>&D,int n){
    cir(i,0,n) D[0][1<<i]=0;
}
void error_throw1(int val){cout<<0<<'\n';exit(val);}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,m;cin>>n>>m;vector<VI> C,D,W;
    if(n==1) error_throw1(0);
    const int _sz=1<<n;assign(C,n,n,_inf);
    assign(D,n,_sz,_inf);assign(W,_sz,_sz,_inf);
    cir(i,0,m){
        lint u,v,w;cin>>u>>v>>w;--u,--v;
        C[u][v]=min(C[u][v],w);
        C[v][u]=min(C[v][u],w);
    }
    init(W,C,_sz,n);initD(D,n);
    lint ans=_inf;
    cir(step,1,n){
        cir(i,1,_sz) cir(j,1,_sz){
            if((i&j)!=j||i==j) continue;
            D[step][i]=min(D[step][i],
                D[step-1][j]+W[i][j]*step);
        }
        ans=min(ans,D[step][_sz-1]);
    }
    cout<<ans<<'\n';
    return 0;
}