#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
static constexpr auto _inf=(int)(1e9+7);
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n,m;cin>>n>>m;
    vector<string> mp(n);
    for(auto&i:mp) cin>>i;
    static const auto mx=array<int,4>{1,-1,0,0};
    static const auto my=array<int,4>{0,0,1,-1};
    vector<vector<array<pair<int,int>,4>>> vx(n,vector<array<pair<int,int>,4>>(m));
    cir(i,0,n) cir(j,0,m) cir(d,0,4){
        auto px=i,py=j;
        while(px>-1&&px<n&&py>-1&&py<m&&mp[px][py]==mp[i][j]){
            px+=mx[d];py+=my[d];
        }
        vx[i][j][d]={px,py};
    }
    vector<vector<pair<int,int>>> pos(256);
    cir(i,0,n) cir(j,0,m) pos[mp[i][j]].emplace_back(i,j);
    string s;cin>>s;s+='*';
    vector<vector<int>> f(n,vector<int>(m,_inf));
    vector<vector<int>> dis(n,vector<int>(m,_inf));
    f[0][0]=0;
    for(auto&c:s){
        auto mn=_inf;
        queue<pair<int,int>> q;
        cir(i,0,n) cir(j,0,m){
            if(f[i][j]<_inf) q.emplace(i,j),dis[i][j]=f[i][j];
        }
        while(!q.empty()){
            const auto[x,y]=q.front();q.pop();
            cir(i,0,4){
                const auto[nx,ny]=vx[x][y][i];
                if(nx<0||nx>n-1||ny<0||ny>m-1) continue;
                if(dis[x][y]+1<dis[nx][ny]){
                    dis[nx][ny]=dis[x][y]+1;
                    q.emplace(nx,ny);
                }
            }
        }
        for(auto&x:f) fill(x.begin(),x.end(),_inf);
        for(auto&[x,y]:pos[c]) f[x][y]=dis[x][y];
        for(auto&x:dis) fill(x.begin(),x.end(),_inf);
    }
    auto ans=_inf;
    for(auto&x:f) ans=min(ans,*min_element(x.begin(),x.end()));
    cout<<ans+s.size()<<'\n';
    return 0;
}
