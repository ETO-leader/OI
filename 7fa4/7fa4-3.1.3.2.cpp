#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
vector<string> mp;
struct Point{
    int x,y;
    Point operator+(const Point&P) const{
        return {x+P.x,y+P.y};
    }
    bool operator==(const Point&P) const{
        return x==P.x&&y==P.y;
    }
    bool out(int n,int m){
        return x>=0&&x<n&&y>=0&&y<m&&mp[x][y]!='*';
    }
};
vector<Point> mv{{0,1},{0,-1},{1,0},{-1,0}};
struct PointHashing{
    hash<int> HASH;
    auto operator()(const Point&P) const{
        return HASH(P.x)+HASH(P.y);
    }
};
unordered_map<Point,int,PointHashing> D;
unordered_map<Point,bool,PointHashing> vis;
void bfs(Point&s,int n,int m){
    queue<Point> q;q.push(s);
    vis[s]=true;
    while(!q.empty()){
        auto f=q.front();q.pop();
        for(auto&i:mv){
            auto mt=f+i;
            if(mt.out(n,m)&&!vis[mt]){
                vis[mt]=true;D[mt]=D[f]+1;q.push(mt);
            } 
        }
    }
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,m;cin>>n>>m;mp.resize(n);
    Point s,e;
    cir(i,0,n){
        cin>>mp[i];
        cir(j,0,m){
            if(mp[i][j]=='S') s={i,j};
            if(mp[i][j]=='T') e={i,j};
        }
    }
    bfs(s,n,m);
    cout<<(!vis[e]?-1:D[e])<<'\n';
    return 0;
}