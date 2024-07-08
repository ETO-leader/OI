#include<bits/stdc++.h>
using namespace std;
using VI=vector<int>;
using VVI=vector<VI>;
struct Point{
    int x,y;
    Point&operator+=(Point&P){
        x+=P.x,y+=P.y;return *this;}
    bool unout(int n){return x>=0&&x<n&&y>=0&&y<n;}
};
vector<Point> mv{{1,0},{-1,0},{0,1},{0,-1}};
VVI mp;
template<typename T>
struct HeapNode{
    T v;int w,k;
    inline bool operator<(const HeapNode&hp) const{
        return w>hp.w;
    }
};
const int _inf=1e9+7;
vector<VVI> bfs(int n,int k,int a,int b,int c){
    vector<VVI> res(n,VVI(n,VI(k,_inf)))
        ,vis(n,VVI(n,VI(k)));
    priority_queue<HeapNode<Point>> pq;
    pq.push({{0,0},0,k});res[0][0][k-1]=0;
    while(!pq.empty()){
        auto f=pq.top();pq.pop();
        if(vis[f.v.x][f.v.y][f.k-1]) continue;
        vis[f.v.x][f.v.y][f.k-1]=true;
        for(auto&i:mv){
            auto nf=f;nf.v+=i;nf.k--;
            if(!nf.v.unout(n)) continue;
            if(!((~i.x)&&(~i.y))) nf.w+=b;
            if(mp[nf.v.x][nf.v.y]) nf.k=k,nf.w+=a;
            if(!nf.k) nf.k=k,nf.w+=(a+c)*(!(nf.v.x==n-1&&nf.v.y==n-1));
            if(vis[nf.v.x][nf.v.y][nf.k-1]||
                res[nf.v.x][nf.v.y][nf.k-1]<=nf.w) continue;
            pq.push(nf);res[nf.v.x][nf.v.y][nf.k-1]=nf.w;
        }
    }
    return res;
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,k,a,b,c;cin>>n>>k>>a>>b>>c;
    mp.assign(n,VI(n));
    for(auto&i:mp) for(auto&j:i) cin>>j;
    auto r=bfs(n,k,a,b,c);
    cout<<(*min_element(r[n-1][n-1].begin(),
        r[n-1][n-1].end()))<<'\n';
    return 0;
}