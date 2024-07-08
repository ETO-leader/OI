#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
using VI=vector<lint>;
static constexpr lint _inf=1e18+7;
class minc_fgraph{
private:
    struct edge{
        int v,rev;lint c,w;
    };
    vector<vector<edge>> G;
    bool spfa(int s,int t,lint&cost,lint&flow){
        queue<int> λ;λ.push(s);
        VI dist(G.size(),_inf),fa(G.size(),
            -1),fe(G.size()),inq(G.size());
        inq[s]=true;dist[s]=0;
        while(!λ.empty()){
            auto u=λ.front();λ.pop();inq[u]=false;
            int cnx=0;
            for(auto&[v,rev,c,w]:G[u]){
                if(w){
                    if(dist[u]+c<dist[v]){
                        dist[v]=dist[u]+c;
                        fa[v]=u;fe[v]=cnx;
                        if(!inq[v]) λ.push(v),inq[v]=true;
                    }
                }
                ++cnx;
            }
        }
        if(dist[t]>_inf-1) return false;
        int u=t;lint minfl=_inf;
        while(u!=s){
            int egid=fe[u];u=fa[u];
            minfl=min(minfl,G[u][egid].w);
        }
        cost+=dist[t]*minfl;u=t;
        while(u!=s){
            int egid=fe[u],ux=u;u=fa[u];
            G[u][egid].w-=minfl;
            G[ux][G[u][egid].rev].w+=minfl;
        }
        return flow+=minfl,true;
    }
public:
    void insert(int u,int v,lint c,lint w){
        G[u].push_back({v,
            (int)(G[v].size()),c,w});
        G[v].push_back({u,
            (int)(G[u].size())-1,-c,0});
    }
    auto get(int s,int t){
        lint cst=0,flw=0;
        while(spfa(s,t,cst,flw));
        return pair(cst,flw);
    }
    minc_fgraph(int n):G(n){}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,m,s,t;cin>>n>>m>>s>>t;
    minc_fgraph gr(n+1);
    cir(i,0,m){
        int u,v;lint c,w;cin>>u>>v>>c>>w;
        gr.insert(u,v,w,c);
    }
    auto[cost,flow]=gr.get(s,t);
    cout<<flow<<'\n'<<cost<<'\n';
    return 0;
}
