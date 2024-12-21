#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
struct Point{
    int x,y;
    Point operator+(const Point&P) const{
        return {x+P.x,y+P.y};}
    bool operator==(const Point&P) const{
        return x==P.x&&y==P.y;}
    bool unout(int n,int m){
        return x>=0&&x<n&&y>=0&&y<m;}
};
vector<Point> mv{{0,1},{0,-1},{1,0},{-1,0}};
struct PointHashing{
    hash<int> HASH;
    auto operator()(const Point&P) const{
        return HASH(P.x)+HASH(P.y);}
};
vector<vector<int>> G;
template<typename T>
struct extvec{
    vector<T> vec,vis;int n,m;
    extvec(int _n=0,int _m=0):
        n(_n),m(_m),vec(_n*_m),vis(_n*_m){}
    int pot(Point&P){return (P.x*(n-1)+P.y);}
    T&operator[](Point&P){vis[pot(P)]=true;return vec[pot(P)];}
    bool count(Point&P){return vis[pot(P)];}
    void res(int _n,int _m){(*this)=extvec(_n,_m);}
};
extvec<int> D;extvec<int> vis;
const queue<Point> EmpQueue;
void bfs(Point u,int n,int m){
    deque<queue<Point>> q(10);
    D[u]=G[u.x][u.y];q.front().push(u);
    auto expr=[&q](){bool res=true;for(auto&i:q)
        res&=i.empty();return (!res);};
    while(expr()){
        while(q.front().empty())
            q.pop_front(),q.push_back(EmpQueue);
        auto f=q.front().front();q.front().pop();
        if(vis[f]) continue;vis[f]=true;
        for(auto&i:mv){
            auto ux=f+i;
            if(ux.unout(n,m)&&(!vis[ux])&&
                (!D.count(ux)||D[ux]>D[f]+G[ux.x][ux.y])){
                q[G[ux.x][ux.y]].push(ux);
                D[ux]=D[f]+G[ux.x][ux.y];
            }
        }
    }
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,m;cin>>n>>m;D.res(n,m);vis.res(n,m);
    G.resize(n,vector<int>(m));
    for(auto&i:G) for(auto&j:i) cin>>j;
    bfs({0,0},n,m);Point e={n-1,m-1};
    cout<<D[e]<<'\n';
    return 0;
}