#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
static constexpr auto _inf=(int)(1e9+7);
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n,m;cin>>n>>m;
    vector<vector<int>> s(n,vector<int>(m));
    for(auto&x:s) for(auto&i:x) cin>>i;
    static const auto mx=array<int,4>{1,-1,0,0};
    static const auto my=array<int,4>{0,0,1,-1};
    queue<pair<int,int>> q;
    q.emplace(n-1,m-1);
    vector<vector<pair<int,int>>> nxt(n,vector<pair<int,int>>(m));
    vector<vector<int>> dis(n,vector<int>(m,_inf));
    dis[n-1][m-1]=1;
    while(!q.empty()){
        const auto[x,y]=q.front();q.pop();
        if(s[x][y]) continue;
        cir(i,0,4){
            const auto nx=x+mx[i],ny=y+my[i];
            if(nx<0||nx>n-1||ny<0||ny>m-1) continue;
            if(s[nx][ny]) continue;
            if(dis[nx][ny]>dis[x][y]+1){
                dis[nx][ny]=dis[x][y]+1;
                nxt[nx][ny]={x,y};
                q.emplace(nx,ny);
            }
        }
    }
    if(dis[0][0]==_inf){
        cout<<"Noway!"<<'\n';
    }else{
        cout<<dis[0][0]<<'\n';
        auto cur=make_pair(0,0);
        cir(i,0,dis[0][0]){
            cout<<cur.first+1<<' '<<cur.second+1<<'\n';
            cur=nxt[cur.first][cur.second];
        }
    }
    return 0;
}
