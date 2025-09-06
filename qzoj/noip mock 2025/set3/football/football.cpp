#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto _infl=(lint)(1e16l);
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int lx,ly;cin>>lx>>ly;
    lint a,b,c;cin>>a>>b>>c;
    int n;cin>>n;
    vector<int> x(n),y(n);
    ++lx;++ly;
    cir(i,0,n) cin>>x[i]>>y[i];
    vector<vector<lint>> dis(lx,vector<lint>(ly,_infl));
    queue<pair<int,int>> q;
    static const auto mx=array<int,4>{-1,1,0,0};
    static const auto my=array<int,4>{0,0,-1,1};
    cir(i,0,n){
        dis[x[i]][y[i]]=0;
        q.emplace(x[i],y[i]);
    }
    while(!q.empty()){
        const auto[ux,uy]=q.front();q.pop();
        cir(i,0,4){
            const auto nx=ux+mx[i];
            const auto ny=uy+my[i];
            if(nx>-1&&nx<lx&&ny>-1&&ny<ly&&dis[nx][ny]>dis[ux][uy]+c){
                dis[nx][ny]=dis[ux][uy]+c;
                q.emplace(nx,ny);
            }
        }
    }
    vector<vector<vector<lint>>> f(lx,vector<vector<lint>>(ly,vector<lint>(5,_infl)));
    vector<vector<vector<int>>> vis(lx,vector<vector<int>>(ly,vector<int>(5)));
    priority_queue<tuple<lint,int,int,int>,vector<tuple<lint,int,int,int>>,greater<>> uq;
    f[x[0]][y[0]][4]=0;
    uq.emplace(0,x[0],y[0],4);
    while(!uq.empty()){
        const auto[w,ux,uy,dir]=uq.top();uq.pop();
        // clog<<w<<' '<<ux<<' '<<uy<<' '<<dir<<'\n';
        if(vis[ux][uy][dir]) continue;
        vis[ux][uy][dir]=true;
        if(dir<4){
            if(f[ux][uy][4]>w+dis[ux][uy]){
                f[ux][uy][4]=w+dis[ux][uy];
                uq.emplace(f[ux][uy][4],ux,uy,4);
            }
            const auto nx=ux+mx[dir];
            const auto ny=uy+my[dir];
            if(nx>-1&&nx<lx&&ny>-1&&ny<ly&&f[nx][ny][dir]>w+a){
                f[nx][ny][dir]=w+a;
                uq.emplace(f[nx][ny][dir],nx,ny,dir);
            }
        }else{
            cir(i,0,4){
                const auto nx=ux+mx[i];
                const auto ny=uy+my[i];
                if(nx>-1&&nx<lx&&ny>-1&&ny<ly&&f[nx][ny][4]>f[ux][uy][4]+c){
                    f[nx][ny][4]=f[ux][uy][4]+c;
                    uq.emplace(f[nx][ny][4],nx,ny,4);
                }
            }
            cir(i,0,4) if(f[ux][uy][i]>f[ux][uy][4]+b){
                f[ux][uy][i]=f[ux][uy][4]+b;
                uq.emplace(f[ux][uy][i],ux,uy,i);
            }
        }
    }
    cout<<*min_element(f[x[n-1]][y[n-1]].begin(),f[x[n-1]][y[n-1]].end())<<'\n';
    return 0;
}
