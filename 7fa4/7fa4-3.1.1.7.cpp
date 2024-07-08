#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
const string Error="No solution.\n";
struct graph{
    struct edge{int v,col,rid,Eid;bool vis;};
    vector<vector<edge>> G;
    vector<bool> vis,vist;
    vector<int> fath,es;int Ecnt,n;
    int exc(int c){return c==1?2:1;}
    void init(int u,int f,int Tcol){
        fath[u]=f;vis[u]=true;
        for(auto&i:G[u]){
            auto&Reg=G[i.v][i.rid];
            if(i.vis) continue;
            i.vis=Reg.vis=true;i.col=Reg.col=exc(Tcol);
            if(!vis[i.v]) init(i.v,u,i.col);
        }
    }
    void insert(int u,int v){
        es[u]++;es[v]++;
        G[u].push_back({v,0,(int)(G[v].size()),(++Ecnt),false});
        if(u!=v) G[v].push_back({u,0,(int)(G[u].size())-1,Ecnt,false});
    }
    void Gstep(int u,int f){
        for(auto&i:G[u]){
            assert(G[i.v].size()>i.rid);
            auto&Reg=G[i.v][i.rid];
            if(i.v==f){
                i.col=Reg.col=exc(i.col);
                break;
            }
        }
    }
    int mov(int u){
        while(u&&G[u].size()<3){
            Gstep(u,fath[u]);u=fath[u];
        }
        return u;
    }
    bool chk_root(int u){
        unordered_set<int> us;
        for(auto&i:G[u]) us.insert(i.col);
        return us.size()==2||es[u]<2;
    }
    bool solve(int u){
        vis[u]=true;
        vector<int> retE_list;
        int col=2;
        for(auto&i:G[u]){
            auto&Reg=G[i.v][i.rid];
            if(i.vis){
                retE_list.push_back(i.v);
            }else{
                (col=exc(col)),(i.col=Reg.col=col),
                (i.vis=Reg.vis=true);
                if(!vis[i.v]) init(i.v,0,col);
            }
        }
        vector<bool> viss(n+1);
        if(chk_root(u)) return true;
        if(retE_list.empty()) return false;
        Gstep(u,retE_list.front());
        return mov(retE_list.front());
    }
    void rans(int u,vector<int>&ans,vector<bool>&viss){
        viss[u]=true;
        for(auto&i:G[u]){
            ans[i.Eid]=i.col;if(!viss[i.v]) rans(i.v,ans,viss);
        }
    }
    void print(){
        vector<int> ans(Ecnt+1);
        vector<bool> viss(n);
        cir(i,1,n+1) if(!viss[i]) rans(i,ans,vis);
        for(auto&i:ans) cout<<(i==1?'R':'B');
        cout<<'\n';
    }
    void run(){
        bool kx=true;
        cir(i,1,n+1) if(!vis[i]) kx&=solve(i);
        if(!kx){cout<<Error;return;}
        print();
    }
    graph(int _n):G(_n+1),fath(_n+1),vis(_n+1),
        Ecnt(-1),n(_n),es(_n+1),vist(_n+1){}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int T;cin>>T;
    while(T--){
        int n,m;cin>>n>>m;
        graph G(n);
        cir(i,0,m){
            int u,v;cin>>u>>v;G.insert(u,v);
        }
        G.run();
    }
    return 0;
}
//Duliu