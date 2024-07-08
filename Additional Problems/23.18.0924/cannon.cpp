#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
using VI=vector<lint>;
static constexpr lint _inf=1e18+7;
static constexpr int adc=1007;
template<typename T,const T _infx=_inf>
class graph{
private:
    struct edge{int u,v;T cap,flow;edge*rev;};
    vector<vector<edge>> G;
    vector<int> h,cur;vector<bool> vis;
    vector<vector<size_t>> rid;size_t _nx;
    bool bfs(int u,int v){
        fill(vis.begin(),vis.end(),false);
        fill(h.begin(),h.end(),0);
        queue<int> q;q.push(u);
        while(!q.empty()){
            auto f=q.front();q.pop();
            if(vis[f]) continue;
            vis[f]=true;
            for(auto&i:G[f]){
                if(vis[i.v]||i.cap<=i.flow) continue;
                q.push(i.v);h[i.v]=h[f]+1;
            }
        }
        return vis[v];
    }
    T dfs(int u,T flow,int v){
        if(u==v||!flow) return flow;
        T flx=0,fl;int&i=cur[u];
        for(;i<G[u].size();++i){
            auto&E=G[u][i];
            if(h[u]+1==h[E.v]&&
                (fl=dfs(E.v,min(flow,E.cap-E.flow),v))){
                E.flow+=fl;E.rev->flow-=fl;flx+=fl;flow-=fl;
                if(!flow) break;
            }
        }
        return flx;
    }
    void reid(){
        cir(i,0,_nx){
            cir(j,0,rid[i].size())
                G[G[i][j].v][rid[i][j]].rev=&G[i][j];
        }
    }
public:
    void insert(int u,int v,T cap){
        if(u==v) return;
        G[u].push_back({u,v,cap,0,nullptr});
        G[v].push_back({v,u,0,0,nullptr});
        rid[u].push_back(G[v].size()-1);
        rid[v].push_back(G[u].size()-1);
    }
    T dinic(int u,int v){
        T flow=0;reid();
        while(bfs(u,v)){
            fill(cur.begin(),cur.end(),0);
            flow+=dfs(u,_infx,v);
        }
        return flow;
    }
    graph(int _n):G(_n),rid(_n),
        vis(_n),h(_n),cur(_n),_nx(_n){}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    freopen("cannon.in","r",stdin);
    freopen("cannon.out","w",stdout);
    int n,m;cin>>n>>m;
    vector<VI> a(n,VI(m));
    for(auto&i:a) for(auto&j:i) cin>>j;
    a.insert(a.begin(),VI(m));
    a.push_back(VI(m));
    for(auto&i:a){
        i.insert(i.begin(),0);
        i.push_back(0);
    }
    n+=2;m+=2;
    graph<lint> G(n*m*2+7);
    auto idu=[&](int x,int y){
        return x*m+y+1;
    };
    auto idl=[&](int x,int y){
        return idu(x,y)+n*m;
    };
    cir(i,0,n) cir(j,0,m){
        G.insert(idl(i,j),idu(i,j),_inf);
    }
    const int s=0,t=n*m*2+5;
    lint cnx=0;
    cir(i,0,n) cir(j,0,m) if(a[i][j]<0){
        if(a[i][j]==-1){
            lint cpx=0;
            for(int x=i;x;--x){
                cpx=max(cpx,a[x][j]);
                G.insert(idu(x-1,j),
                    idu(x,j),adc-cpx);
            }
            G.insert(idu(i,j),t,_inf);
            G.insert(s,idu(0,j),_inf);
        }else if(a[i][j]==-2){
            lint cpx=0;
            cir(x,i,n-1){
                cpx=max(cpx,a[x][j]);
                G.insert(idu(x+1,j),
                    idu(x,j),adc-cpx);
            }
            G.insert(idu(i,j),t,_inf);
            G.insert(s,idu(n-1,j),_inf);
        }else if(a[i][j]==-3){
            lint cpx=0;
            for(int y=j;y;--y){
                cpx=max(cpx,a[i][y]);
                G.insert(idl(i,y),
                    idl(i,y-1),adc-cpx);
            }
            G.insert(idl(i,0),t,_inf);
            G.insert(s,idl(i,j),_inf);
        }else{
            lint cpx=0;
            cir(y,j,m-1){
                cpx=max(cpx,a[i][y]);
                G.insert(idl(i,y),
                    idl(i,y+1),adc-cpx);
            }
            G.insert(idl(i,m-1),t,_inf);
            G.insert(s,idl(i,j),_inf);
        }
        ++cnx;
    }
    cout<<cnx*adc-G.dinic(s,t)<<'\n';
    return 0;
}
