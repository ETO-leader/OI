#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n;cin>>n;
    vector<string> info(n);
    for(auto&x:info) cin>>x;
    vector<vector<int>> a(n,vector<int>(n));
    vector<int> px;
    for(auto&x:a) for(auto&i:x) cin>>i,px.emplace_back(i);
    sort(px.begin(),px.end());
    const auto ck=accumulate(info.begin(),info.end(),0,[&](auto a,auto b){
        return a+count(b.begin(),b.end(),'K');
    });
    auto bfs=[&](int l,int r){
        static const auto mx=array<int,8>{0,0,-1,1,-1,1,-1,1};
        static const auto my=array<int,8>{-1,1,0,0,-1,-1,1,1};
        auto cnt=0;
        queue<pair<int,int>> q;
        vector<vector<int>> vis(n,vector<int>(n));
        cir(i,0,n) cir(j,0,n) if(a[i][j]>l-1&&a[i][j]<r+1&&info[i][j]=='P'){
            q.emplace(i,j);vis[i][j]=true;
        }
        while(!q.empty()){
            const auto[x,y]=q.front();q.pop();
            cnt+=info[x][y]=='K';
            cir(i,0,8){
                const auto nx=x+mx[i],ny=y+my[i];
                if(nx>-1&&nx<n&&ny>-1&&ny<n&&(!vis[nx][ny])&&a[nx][ny]>l-1&&a[nx][ny]<r+1){
                    vis[nx][ny]=true;
                    q.emplace(nx,ny);
                }
            }
        }
        return cnt==ck;
    };
    auto ans=numeric_limits<int>::max();
    auto r=0;
    cir(l,0,n*n){
        while(r<n*n&&(!bfs(px[l],px[r]))) ++r;
        if(r<n*n) ans=min(ans,px[r]-px[l]);
    }
    cout<<ans<<'\n';
    return 0;
}
