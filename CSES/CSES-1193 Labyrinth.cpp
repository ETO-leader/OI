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
    bool unout(int n,int m){
        return x>=0&&x<n&&y>=0&&y<m&&mp[x][y]!='#';
    }
};
vector<Point> mv{{0,1},{0,-1},{1,0},{-1,0}};
template<typename T>
struct extvector{
    vector<vector<T>> vec;
    void resize(int n,int m){vec.assign(n,vector<T>(m));}
    T&operator[](Point&p){return vec[p.x][p.y];}
};
extvector<int> D,vis;
extvector<pair<Point,char>> F;
string mvi="RLDU";
char mvx(Point&ix){cir(i,0,4) if(mv[i]==ix) return mvi[i];}
void bfs(Point&s,int n,int m){
    queue<Point> q;q.push(s);
    vis[s]=true;
    while(!q.empty()){
        auto f=q.front();q.pop();
        for(auto&i:mv){
            auto mt=f+i;
            if(mt.unout(n,m)&&!vis[mt]){
                F[mt]=make_pair(f,mvx(i));
                vis[mt]=true;D[mt]=D[f]+1;q.push(mt);
            }
        }
    }
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,m;cin>>n>>m;mp.resize(n);
    D.resize(n,m);vis.resize(n,m);F.resize(n,m);
    Point s,e;
    cir(i,0,n){
        cin>>mp[i];
        cir(j,0,m){
            if(mp[i][j]=='A') s={i,j};
            if(mp[i][j]=='B') e={i,j};
        }
    }
    bfs(s,n,m);
    if(!vis[e]){cout<<"NO\n";exit(0);}
    cout<<"YES\n"<<D[e]<<'\n';
    stringstream ss;
    while(!(e==s)) ss<<F[e].second,e=F[e].first;
    auto st=ss.str();reverse(st.begin(),st.end());
    cout<<st<<'\n';
    return 0;
}