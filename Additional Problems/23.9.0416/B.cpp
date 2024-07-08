#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
struct edge_t{int u,v;bool rev_tag;};
struct edge{int v;edge_t*eid;};
vector<vector<edge>> G;
vector<lint> tgl;
void dfs(int u,int f=0){
    for(auto&[v,ix]:G[u]) if(v!=f){
        ix->rev_tag=(u!=ix->u);
        dfs(v,u);
    }
}
void rdfs(vector<lint>&ax,int u,int f=0,lint w=0){
    ax[u]+=(w+=tgl[u]);
    for(auto&[v,ix]:G[u]) if(v!=f) rdfs(ax,v,u,w);
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n;cin>>n;vector<edge_t> ve(n-1);
    G.resize(n+1);tgl.resize(n+1);
    for(auto&[u,v,rt]:ve) cin>>u>>v;
    for(auto&i:ve){
        G[i.u].push_back({i.v,&i});
        G[i.v].push_back({i.u,&i});
    }
    dfs(1);
    int q;lint aladd=0;cin>>q;
    cir(i,0,q){
        int op,x;lint w;cin>>op>>x>>w;
        --x,--op;
        if(!op){
            if(!ve[x].rev_tag) aladd+=w,tgl[ve[x].v]-=w;
            else tgl[ve[x].u]+=w;
        }else{
            if(ve[x].rev_tag) aladd+=w,tgl[ve[x].u]-=w;
            else tgl[ve[x].v]+=w;
        }
    }
    vector<lint> ans(n+1,aladd);
    rdfs(ans,1);
    cir(i,1,n+1) cout<<ans[i]<<'\n';
    return 0;
}
