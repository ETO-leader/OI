#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
#ifdef EK_algorithm
template<typename T>
class flowgraph{
private:
    struct edge{int u,v;T cap,flow;edge* rev;};
    vector<vector<edge>> G;
    vector<vector<int>> RID;
    using est=edge*;
    int _n;
    bool bfs(vector<T>&Fl,vector<est>&F,queue<int>&q,int v){
        while(!q.empty()){
            auto f=q.front();q.pop();
            for(auto&i:G[f]){
                if((!Fl[i.v])&&(i.flow<i.cap)){
                    assert(!(i.cap<=i.flow));
                    F[i.v]=&i;
                    Fl[i.v]=min(Fl[f],i.cap-i.flow);
                    q.push(i.v);
                }
            }
            if(Fl[v]) return true;
        }
        return false;
    }
    T _inf;
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
            Fl[u]=_inf;
            if(!bfs(Fl,F,q,v)) break;
            flow+=Fl[v];
            for(int ux=v;ux!=u;ux=F[ux]->u){
                assert((F[ux]->rev)!=nullptr);
                (F[ux]->flow+=Fl[v]);(F[ux]->rev->flow)-=Fl[v];
            }
        }
        return flow;
    }
    void newedge(int u,int v,int cap){
        if(u==v) return;
        G[u].push_back({u,v,cap,0,nullptr});
        G[v].push_back({v,u,0,0,nullptr});
        RID[u].push_back(G[v].size()-1);
        assert(G[v][RID[u].back()].v==u);
        RID[v].push_back(G[u].size()-1);
    }
    flowgraph(int __n,T INF):_inf(INF),G(__n),_n(__n),RID(__n){}
};
using lint=long long;
const lint _inf=1e18+7;
#else
using lint=long long;
const lint _inf=1e18+7;
template<typename T,const T _infx=_inf>
class flowgraph{
private:
    struct edge{int u,v;T cap,flow;edge*rev;};
    vector<vector<edge>> G;
    vector<int> H,cur;vector<bool> vis;
    vector<vector<size_t>> RID;size_t _nx;
    bool bfs(int u,int v){
        fill(vis.begin(),vis.end(),false);
        fill(H.begin(),H.end(),0);
        queue<int> q;q.push(u);
        while(!q.empty()){
            auto f=q.front();q.pop();
            if(vis[f]) continue;
            vis[f]=true;
            for(auto&i:G[f]){
                if(vis[i.v]||i.cap<=i.flow) continue;
                q.push(i.v);H[i.v]=H[f]+1;
            }
        }
        return vis[v];
    }
    T dfs(int u,T flow,int v){
        if(u==v||!flow) return flow;
        T flx=0,fl;int&i=cur[u];
        for(;i<G[u].size();++i){
            auto&E=G[u][i];
            if(H[u]+1==H[E.v]&&
                (fl=dfs(E.v,min(flow,E.cap-E.flow),v))){
                E.flow+=fl;E.rev->flow-=fl;flx+=fl;flow-=fl;
                if(!flow) break;
            }
        }
        return flx;
    }
    void reid(){
        cir(i,0,_nx){
            cir(j,0,RID[i].size())
                G[G[i][j].v][RID[i][j]].rev=&G[i][j];
        }
    }
public:
    void newedge(int u,int v,T cap){
        if(u==v) return;
        G[u].push_back({u,v,cap,0,nullptr});
        G[v].push_back({v,u,0,0,nullptr});
        RID[u].push_back(G[v].size()-1);
        RID[v].push_back(G[u].size()-1);
    }
    T maxflow(int u,int v){
        T flow=0;reid();
        while(bfs(u,v)){
            fill(cur.begin(),cur.end(),0);
            flow+=dfs(u,_infx,v);
        }
        return flow;
    }
    flowgraph(int _n):G(_n),RID(_n),
        vis(_n),H(_n),cur(_n),_nx(_n){}
};
#endif
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,m;cin>>n>>m;
    flowgraph<lint> G(n+1);
    cir(i,0,m){
        int u,v,cap;cin>>u>>v>>cap;
        G.newedge(u,v,cap);
    }
    cout<<G.maxflow(1,n)<<'\n';
    return 0;
}