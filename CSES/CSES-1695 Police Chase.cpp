#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
const lint _inf=1e18+7;
template<typename T,const T _infx=_inf>
class ek_flowgraph{
private:
    struct edge{int u,v;T cap,flow;edge* rev;};
    vector<vector<edge>> G;
    vector<vector<int>> RID;
    using est=edge*;
    int _n;
    bool bfs(vector<T>&Fl,vector<est>&F,queue<int>&q,int v){
        while(!q.empty()){
            auto f=q.front();q.pop();
            cout<<f<<endl;
            system("pause");
            for(auto&i:G[f]){
                if((!Fl[i.v])&&(i.flow<i.cap)){
                    F[i.v]=&i;
                    Fl[i.v]=min(Fl[f],i.cap-i.flow);
                    q.push(i.v);
                }
            }
            if(Fl[v]) return true;
        }
        return false;
    }
    void reid(){
        cir(i,0,_n){
            cir(j,0,RID[i].size())
                G[G[i][j].v][RID[i][j]].rev=&G[i][j];
        }
    }
public:
    T maxflow(int u,int v){
        T flow=0;reid();
        while(true){
            vector<T> Fl(_n);vector<est> F(_n);
            queue<int> q;q.push(u);
            Fl[u]=_infx;
            if(!bfs(Fl,F,q,v)) break;
            flow+=Fl[v];
            for(int ux=v;ux!=u;ux=F[ux]->u){
                (F[ux]->flow+=Fl[v]);(F[ux]->rev->flow)-=Fl[v];
            }
        }
        return flow;
    }
    void fs(int u,int v){
        vector<T> Fl(_n);vector<est> F(_n);
        queue<int> q;q.push(u);
        bfs(Fl,F,q,v);
    }
    vector<edge>&operator[](size_t x){return G[x];}
    void newedge(int u,int v){
        if(u==v) return;
        G[u].push_back({u,v,1,0,nullptr});
        G[v].push_back({v,u,1,0,nullptr});
        RID[u].push_back(G[v].size()-1);
        RID[v].push_back(G[u].size()-1);
    }
    ek_flowgraph(int __n):G(__n),RID(__n),_n(__n){}
};
void dfs(int u,vector<bool>&vis,ek_flowgraph<lint>&G){
    if(vis[u]) return;
    vis[u]=true;
    for(auto&i:G[u])
        if(i.cap>0) dfs(i.v,vis,G);
}
void run(int u,int v,int n,ek_flowgraph<lint>&G){
    auto CG=G;G.fs(u,v);
    /*vector<bool> vis(n);
    dfs(u,vis,G);
    vis[v]=false;
    cout<<CG.maxflow(u,v)<<'\n';
    cir(i,1,n){
        if(vis[i]) for(auto&j:G[i]){
            if(!vis[j.v]) cout<<i<<' '<<j.v<<'\n';
        }
    }*/
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,m;cin>>n>>m;
    ek_flowgraph<lint> G(n+1);
    cir(i,0,m){
        int u,v;cin>>u>>v;
        G.newedge(u,v);
    }
    run(1,n,n+1,G);
    return 0;
}