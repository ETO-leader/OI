#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
static constexpr auto _inf=(int)(1e9+7);
class graph{
private:
    vector<vector<pair<int,int>>> gr;
public:
    auto link(int u,int v,int d){
        gr[u].emplace_back(v,d);
    }
    auto bfs(int s,int t){
        const auto n=(int)(gr.size());
        vector<vector<int>> f(n,vector<int>(10,_inf));
        f[s][9]=0;
        queue<pair<int,int>> q;q.emplace(s,9);
        while(!q.empty()){
            const auto[u,d]=q.front();q.pop();
            for(auto&[v,vd]:gr[u]) if(d!=vd&&f[v][vd]>f[u][d]+1){
                f[v][vd]=f[u][d]+1;
                q.emplace(v,vd);
            }
        }
        return*min_element(f[t].begin(),f[t].end());
    }
    graph(int _n):gr(_n){}
};
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int m,n;cin>>m>>n;
    vector<vector<int>> a(n,vector<int>(m));
    for(auto&x:a) for(auto&i:x) cin>>i;
    graph gr(n*m);
    cir(i,0,n) cir(j,0,m){
        auto cnt=-1;
        for(auto dx:{-1,0,1}) for(auto dy:{-1,0,1}) if(dx||dy){
            const auto nx=i+dx*a[i][j];
            const auto ny=j+dy*a[i][j];
            ++cnt;
            if(nx<0||nx>n-1||ny<0||ny>m-1) continue;
            gr.link(i*m+j,nx*m+ny,cnt);
        }
    }
    const auto ans=gr.bfs(0,n*m-1);
    if(ans==_inf) cout<<"NEVER"<<'\n';
    else cout<<ans<<'\n';
    return 0;
}
