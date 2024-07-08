#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
using VI=vector<lint>;
static constexpr int upx=1e18+7;
class graph{
private:
    const int lgx=log2(upx)+2;
    struct edge{int v,w;};
    vector<vector<edge>> G;
    VI D,vis,hvs,pre;
    vector<VI> up,upw;
    static auto&cksum(lint&a,lint b){
        return a=((a+b)>upx?upx:a+b);
    }
    auto dfs(int u){
        if(vis[u]) return D[u];
        for(auto&[v,w]:G[u]) 
            cksum(D[u],dfs(v));
        return D[u];
    }
    void rebuild(int u){
        if(vis[u]) return;
        vector<edge> ne;
        lint cnx=0,mx=0,mxid=0,mxv=0,idx=0;
        for(auto&[v,w]:G[u]){
            pre[idx++]=cnx;
            if(mx<D[v]+1) mx=D[v],mxid=idx,mxv=v;
            if((cnx+=D[v])>upx) break;
            rebuild(v);
        }
        up[u][0]=mxv;upw[u][0]=pre[mxid];
        cir(i,1,lgx){
            auto upk=up[u][i-1];
            up[u][i]=up[upk][i-1];
            upw[u][i]=upw[u][i-1]+upw[upk][i-1];
        }
        hvs[u]=mxid;
    }

};
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    freopen("c.in","r",stdin);
    freopen("c.out","w",stdout);
    
    return 0;
}
