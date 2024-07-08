#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
#define res(x) (x).resize(n+1)
using namespace std;
vector<int> dfn,low,st,ins,id;
vector<vector<int>> G,scc;
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
        while(tp!=u){
            tp=st.back();st.pop_back();
            scc.back().push_back(tp);
            ins[tp]=false;id[tp]=scccnt;
        }
    }
}
void TRUE(){cout<<"YES\n";exit(0);}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,m;cin>>n>>m;res(G);res(id);
    res(dfn);res(ins);res(low);
    cir(i,0,m){
        int u,v;cin>>u>>v;
        G[u].push_back(v);
    }
    cir(i,1,n+1) if(!dfn[i]) tarjan(i);
    cout<<scccnt<<'\n';
    cir(i,1,n+1) cout<<id[i]<<' ';
    cout<<'\n';
    return 0;
}