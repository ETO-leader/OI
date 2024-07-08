#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
static constexpr auto _inf=(int)(1e9+7);
struct edge_t{int u,v,w;};
class dsu{
private:
    vector<int> f;
public:
    auto findset(int u)->int{
        return u==f[u]?u:(f[u]=findset(f[u]));
    }
    auto merge(int u,int v){
        f[findset(u)]=findset(v);
    }
    dsu(int _n):f(_n){iota(f.begin(),f.end(),0);}
};
class tree{
private:
    struct edge{int v,w;};
    vector<vector<edge>> gr;
    vector<vector<int>> up,mn;
    vector<int> hx,vis;
    static constexpr auto ups=23;
    auto dfs(int u,int f=0,int fw=0)->void{
        vis[u]=true;
        up[u][0]=f;mn[u][0]=fw;hx[u]=hx[f]+1;
        cir(i,1,ups){
            up[u][i]=up[up[u][i-1]][i-1];
            mn[u][i]=min(mn[u][i-1],mn[up[u][i-1]][i-1]);
        }
        for(auto&[v,w]:gr[u]) if(v!=f) dfs(v,u,w);
    }
    auto minw(int u,int v){
        auto res=_inf;
        if(hx[u]<hx[v]) swap(u,v);
        cir(i,0,ups) if((hx[u]-hx[v])&(1<<i))
            res=min(res,mn[u][i]),u=up[u][i];
        if(u==v) return res;
        for(auto i=ups-1;~i;--i) if(up[u][i]!=up[v][i])
            res=min({res,mn[u][i],mn[v][i]}),u=up[u][i],v=up[v][i];
        assert(up[u][0]);
        return min({res,mn[u][0],mn[v][0]});
    }
public:
    auto insert(int u,int v,int w){
        gr[u+1].push_back({v+1,w});
        gr[v+1].push_back({u+1,w});
    }
    auto init(){
        cir(i,0,(int)(vis.size())) if(!vis[i]) dfs(i);
    }
    auto check(int u,int v){return minw(u+1,v+1);}
    tree(int _n):gr(_n+1),up(_n+1,vector<int>(ups)),    
        mn(_n+1,vector<int>(ups)),hx(_n+1),vis(_n+1){}
};
class nodegen{
private:
    int cnt;
public:
    auto gen(){return cnt++;}
    auto count(){return cnt;}
    nodegen():cnt(0){}
};
auto bfs(auto&gr,deque<int> q){
    vector<int> f(gr.size()),vis(gr.size());
    for(auto&i:q) vis[i]=true;
    while(!q.empty()){
        const auto u=q.front();q.pop_front();
        for(auto&i:gr[u]) if(!vis[i]){
            vis[i]=true;f[i]=f[u]+1;q.push_back(i);
        }
    }
    return f;
}
auto build(auto&mp,auto&pid,int n,int m){
    vector<vector<int>> gr(n*m*2),fgr(n*m*2);
    cir(i,0,n) cir(j,0,m) cir(x,0,2){
        if(mp[i][j]!='#'){
            if(i&&mp[i-1][j]!='#'){
                gr[pid[i][j][x]].push_back(pid[i-1][j][x]);
            }
            if(i<n-1&&mp[i+1][j]!='#'){
                gr[pid[i][j][x]].push_back(pid[i+1][j][x]);
            }
            if(j&&mp[i][j-1]!='#'){
                gr[pid[i][j][x]].push_back(pid[i][j-1][x]);
            }
            if(j<m-1&&mp[i][j+1]!='#'){
                gr[pid[i][j][x]].push_back(pid[i][j+1][x]);
            }
        }
        if(i) fgr[pid[i][j][x]].push_back(pid[i-1][j][x]);
        if(i<n-1) fgr[pid[i][j][x]].push_back(pid[i+1][j][x]);
        if(j) fgr[pid[i][j][x]].push_back(pid[i][j-1][x]);
        if(j<m-1) fgr[pid[i][j][x]].push_back(pid[i][j+1][x]);
    }
    return pair(gr,fgr);
}
auto rmst(vector<edge_t> es,const int c){
    sort(es.begin(),es.end(),[&](auto&a,auto&b){
        return a.w>b.w;
    });
    dsu ds(c);
    tree res(c);
    for(auto&[u,v,w]:es){
        if(ds.findset(u)==ds.findset(v)) continue;
        ds.merge(u,v);
        res.insert(u,v,w);
    }
    res.init();
    return res;
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,m,q;cin>>n>>m>>q;
    vector<string> mp(n);
    for(auto&i:mp) cin>>i;
    vector pid(n,vector<array<int,2>>(m));
    nodegen ngen;
    for(auto&x:pid) for(auto&i:x) for(auto&w:i)
        w=ngen.gen();
    pair<int,int> sp;
    cir(i,0,n) cir(j,0,m) if(mp[i][j]=='#') sp={i,j};
    auto[gr,fgr]=build(mp,pid,n,m);
    deque<int> qx;
    cir(i,0,n) cir(j,0,m) if(mp[i][j]=='v')
        qx.push_back(pid[i][j][0]);
    auto dis=bfs(fgr,qx);
    cir(i,0,n) cir(j,0,m) dis[pid[i][j][1]]=dis[pid[i][j][0]];
    cir(nj,sp.second+1,m) if(mp[sp.first][nj]!='#'){
        if(mp[sp.first-1][nj]!='#'){
            vector<int> nxa,nxb,nya,nyb;
            for(auto&x:gr[pid[sp.first][nj][0]]) if(x!=pid[sp.first-1][nj][0])
                nxa.push_back(x);
            for(auto&x:gr[pid[sp.first][nj][1]]) if(x!=pid[sp.first-1][nj][1])
                nxb.push_back(x);
            for(auto&x:gr[pid[sp.first-1][nj][0]]) if(x!=pid[sp.first][nj][0])
                nya.push_back(x);
            for(auto&x:gr[pid[sp.first-1][nj][1]]) if(x!=pid[sp.first][nj][1])
                nyb.push_back(x);
            gr[pid[sp.first][nj][0]]=nxa;
            gr[pid[sp.first][nj][1]]=nxb;
            gr[pid[sp.first-1][nj][0]]=nya;
            gr[pid[sp.first-1][nj][1]]=nyb;
            gr[pid[sp.first][nj][0]].push_back(pid[sp.first-1][nj][1]);
            gr[pid[sp.first][nj][1]].push_back(pid[sp.first-1][nj][0]);
            gr[pid[sp.first-1][nj][0]].push_back(pid[sp.first][nj][1]);
            gr[pid[sp.first-1][nj][1]].push_back(pid[sp.first][nj][0]);
        }
    }
    vector<edge_t> es;
    map<int,vector<int>> idx;
    cir(i,0,n) cir(j,0,m) cir(x,0,2) idx[pid[i][j][x]]=vector({i,j,x});
    cir(i,0,n*m*2) for(auto&j:gr[i]){
        es.push_back({i,j,min(dis[i],dis[j])});
    }
    auto tr=rmst(es,ngen.count());
    cir(i,0,q){
        int x,y;cin>>x>>y;--x;--y;
        cout<<tr.check(pid[x][y][0],pid[x][y][1])<<'\n';
    }
    return 0;
}
