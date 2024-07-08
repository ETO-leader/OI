#include<bits/stdc++.h>
#define res(x) (x).resize(n+1)
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
vector<vector<int>> G,scc(1),CG;
vector<int> dfn,low,id,st,ins;
using lint=long long;
vector<lint> sccsz(1),C,D;
int dfncnt=0,scccnt=0;
void tarjan(int u){
    dfn[u]=low[u]=++dfncnt;
    st.push_back(u);ins[u]=true;
    for(auto&i:G[u]){
        if(!dfn[i]) tarjan(i),low[u]=min(low[u],low[i]);
        else if(ins[i]) low[u]=min(low[u],dfn[i]);
    }
    if(low[u]==dfn[u]){
        int tp=-1;++scccnt;
        scc.push_back(vector<int>());
        sccsz.push_back(0);
        while(tp!=u){
            tp=st.back(),st.pop_back();
            ins[tp]=false;sccsz[scccnt]+=C[tp];
            scc.back().push_back(tp);id[tp]=scccnt;
        }
    }
}
vector<int> vis,T;
void rebuild(int u){
    if(vis[u]) return;
    vis[u]=true;
    for(auto&i:G[u]){
        if(id[i]!=id[u])
            CG[id[u]].push_back(id[i]),T[id[i]]++;
        rebuild(i);
    }
}
void dp(int u){
    for(auto&i:CG[u]){
        D[i]=max(D[i],D[u]+sccsz[i]);
        if(!(--T[i])) dp(i);
    }
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,m;cin>>n>>m;
    res(G);res(dfn);res(vis);res(low);
    res(id);res(ins);res(C);
    cir(i,1,n+1) cin>>C[i];
    cir(i,0,m){
        int u,v;cin>>u>>v;
        G[u].push_back(v);
    }
    cir(i,1,n+1) if(!dfn[i]) tarjan(i);
    D.resize(scccnt+1);T.resize(scccnt+1);
    CG.resize(scccnt+1);
    cir(i,1,n+1) if(!vis[i])
        CG[0].push_back(id[i]),T[id[i]]=1,rebuild(i);
    dp(0);
    cout<<*max_element(D.begin(),D.end())<<'\n';
    return 0;
}