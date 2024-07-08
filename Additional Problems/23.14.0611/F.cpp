#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using VI=vector<int>;
vector<VI> cnct;
int prv(int x){
    const int n=cnct.size()-1;
    return x==1?n:x-1;
}
struct edge{int v;size_t rid;bool st;};
struct edge_t{
    int u,v;
    edge_t(int _u=0,int _v=0):u(_u),v(_v){}
};
vector<vector<edge>> G;
void insertedge(int u,int v){
    G[u].push_back({v,G[v].size(),false});
    G[v].push_back({u,G[u].size()-1,false});
    cnct[u][v]=cnct[v][u]=true;
}
void init(const int n){
    cir(i,1,n+1){
        insertedge(i,prv(i));
    }
}
auto inputsys(int n,queue<edge_t>&q){
    cnct.clear();G.clear();
    cnct.assign(n+1,VI(n+1));
    G.resize(n+1);init(n);
    vector<edge_t> es(n-3);
    for(auto&[u,v]:es){
        cin>>u>>v;insertedge(u,v);
        if(u>v) swap(u,v);
        if(u!=1&&v!=1) q.push({u,v});
    }
    return es;
}
auto fndnxt(int u,int v){
    int res=-1,idx=-1;
    for(auto&[vx,rid,st]:G[u]){
        if(vx==v&&(!st)) idx=G[v][rid].rid;
        if(vx==1||vx>=v||st) continue;
        if(cnct[vx][v]){res=vx;continue;;}
    }
    return make_pair(res,idx);
}
auto runx(int n,bool revtag,int&cnx){
    queue<edge_t> q;inputsys(n,q);
    vector<edge_t> res;
    while(!q.empty()){
        auto[u,v]=q.front();q.pop();
        if((!cnct[u][1])||(!cnct[v][1])){
            q.push({u,v});continue;
        }
        auto[vx,fid]=fndnxt(u,v);
        if(vx<0){
            q.push({u,v});continue;
        }
        cnct[u][v]=cnct[v][u]=false;
        auto&guf=G[u][fid];
        guf.st=true;G[v][guf.rid].st=true;
        insertedge(1,vx);
        res.push_back(revtag?
            edge_t(1,vx):edge_t(u,v));
    }
    if(revtag) reverse(res.begin(),res.end());
    cnx+=res.size();
    return res;
}
ostream&operator<<(ostream&os,edge_t e){
    return os<<e.u<<' '<<e.v;
}
template<typename T>
ostream&operator<<(ostream&os,vector<T> v){
    for(auto&i:v) os<<i<<'\n';
    return os;
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,cnx=0;cin>>n;
    stringstream ss;
    ss<<runx(n,false,cnx)<<runx(n,true,cnx);
    cout<<cnx<<'\n'<<ss.str();
    return 0;
}
