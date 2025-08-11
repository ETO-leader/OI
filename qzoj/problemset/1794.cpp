#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
static constexpr auto _inf=(int)(1e9+7);
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int T;cin>>T;
    while(T--) []{
        int n;cin>>n;
        int sx,sy,tx,ty;cin>>sx>>sy>>tx>>ty;
        queue<pair<int,int>> q;q.emplace(sx,sy);
        vector<vector<int>> dis(n,vector<int>(n,_inf));
        dis[sx][sy]=0;
        while(!q.empty()){
            const auto[x,y]=q.front();q.pop();
            auto extend=[&](int dx,int dy){
                const auto nx=x+dx,ny=y+dy;
                if(nx<0||nx>n-1||ny<0||ny>n-1) return;
                if(dis[nx][ny]>dis[x][y]+1){
                    dis[nx][ny]=dis[x][y]+1;
                    q.emplace(nx,ny);
                }
            };
            extend(-1,-2);
            extend(-1,+2);
            extend(+1,-2);
            extend(+1,+2);
            extend(-2,-1);
            extend(-2,+1);
            extend(+2,-1);
            extend(+2,+1);
        }
        cout<<dis[tx][ty]<<'\n';
    }();
    return 0;
}
