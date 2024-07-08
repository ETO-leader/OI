#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using ull=unsigned long long;
template<int len>
class base{
private:
    vector<ull> p;
public:
    bool insert(ull x){
        for(int i=len-1;~i;--i){
            if(!(x&(1ull<<i))) continue;
            if(!p[i]) return p[i]=x,true;
            x^=p[i];
        }
        return false;
    }
    base():p(len){}
};
struct edge{int v,id;};
vector<bool> imp,vis;
vector<vector<edge>> G;
vector<ull> ew,tag,dx;
mt19937_64 rnd(time(NULL));
void dfs(int u,int f=0){
    vis[u]=true;
    for(auto&[v,id]:G[u]){
        if(!vis[v]){
            dfs(v,u);dx[u]^=dx[v];
            ew[id]=dx[v];
        }else if(v!=f&&(!ew[id])){
            ew[id]=rnd();
            dx[u]^=ew[id];dx[v]^=ew[id];
        }
    }
}
void init_graph(int m){
    cir(i,0,m){
        int u,v;cin>>u>>v;
        G[u].push_back({v,i});
        G[v].push_back({u,i});
    }
    dfs(1);
}
void init(int n,int m){
    vis.resize(n+1);G.resize(n+1);
    ew.resize(m);tag.resize(n+1);dx.resize(n+1);
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,m;cin>>n>>m;init(n,m);
    ull cnx=0;init_graph(m);
    int q;cin>>q;
    cir(i,0,q) [&](){
        int x;cin>>x;
        vector<int> lst(x);
        for(auto&i:lst) (cin>>i),(--(i^=cnx));
        base<64> b;
        for(auto&i:lst) if(!b.insert(ew[i])){
            cout<<"Disconnected\n";return;
        }
        ++cnx;
        cout<<"Connected\n";
    }();
    return 0;
}
