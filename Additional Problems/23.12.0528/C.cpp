#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using VI=vector<int>;
const int _inf=1e9+7;
vector<VI> C,D,G;
VI col;
int dfs(int u,int f=0){
    const int cu=col[u];
    auto&c=C[u],d=D[u];
    if(col[u]){
        c[(cu-1)^1]=d[(cu-1)^1]=_inf;
        c[cu-1]=0;d[cu-1]=-_inf;
    }else{
        c[0]=c[1]=0;d[0]=d[1]=-_inf;
    }
    int res=0;
    for(auto&i:G[u]) if(i!=f){
        res=max(res,dfs(i,u));
        cir(w,0,2) if(cu+w!=2){    
            int nc=_inf,nd=_inf;
            cir(v,0,2){
                nc=min(nc,C[i][v]+(w!=v));
                nd=min(nd,c[w]+C[i][v]+(w!=v));
            }
            c[w]=max(c[w],nc);d[w]=max(d[w],nd);
        }
    }
    return max(res,min(d[0],d[1]));
}
void resize_all(int n){
    G.clear();col.clear();D.clear();C.clear();
    G.resize(n+1);col.resize(n+1);
    D.assign(n+1,VI(2));C.assign(n+1,VI(2));
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int T;cin>>T;
    while(T--){
        int n;cin>>n;resize_all(n);
        cir(i,1,n+1) cin>>col[i];
        cir(i,0,n-1){
            int u,v;cin>>u>>v;
            G[u].push_back(v);G[v].push_back(u);
        }
        cout<<(dfs(1)+1)/2+1<<'\n';
    }
    return 0;
}