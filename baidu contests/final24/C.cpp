#pragma GCC optimize("Ofast")
#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,ux,uy,vx,vy;cin>>n>>ux>>uy>>vx>>vy;
    vector imp(1007,vector<int>(1007));
    cir(i,0,n){
        int x,y;cin>>x>>y;imp[x][y]=true;
    }
    auto inrange=[&](int u,int v){
        return u>-1&&v>-1&&u<1007&&v<1007;
    };
    vector mx{-1,1,0,0},my{0,0,-1,1};
    deque<pair<int,int>> q;q.push_back({ux,uy});
    vector vis(1007,vector<bool>(1007));
    vector dis(1007,vector(1007,1000000000));
    dis[ux][uy]=0;
    while(!q.empty()){
        const auto[x,y]=q.front();q.pop_front();
        if(vis[x][y]) continue;
        vis[x][y]=true;
        cir(i,0,4){
            const auto nx=x+mx[i],ny=y+my[i];
            if((!inrange(nx,ny))||vis[nx][ny]) continue;
            if(dis[x][y]+imp[nx][ny]>dis[nx][ny]-1) continue;
            dis[nx][ny]=dis[x][y]+imp[nx][ny];
            imp[nx][ny]?q.push_back({nx,ny}):q.push_front({nx,ny});
        }
    }
    cout<<dis[vx][vy]<<'\n';
    return 0;
}
