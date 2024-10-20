#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
using lint=long long;
static constexpr auto _infl=(lint)(1e18l);
int main(){
    ios::sync_with_stdio(false),cin.tie(nullptr);
    int n,m,q;cin>>n>>m>>q;
    vector<tuple<int,int,lint>> es(m);
    for(auto&[u,v,w]:es) cin>>u>>v>>w,--u,--v;
    vector<vector<int>> qx;
    vector<int> banned(m);
    cir(i,0,q){
        int op;cin>>op;
        if(op==1){
            int id;cin>>id;--id;
            qx.push_back({op,id});
            banned[id]=true;
        }else{
            int u,v;cin>>u>>v;--u;--v;
            qx.push_back({op,u,v});
        }
    }
    vector<lint> ans;
    ranges::reverse(qx);
    vector dist(n,vector(n,_infl));
    cir(i,0,m) if(!banned[i]){
        const auto[u,v,w]=es[i];
        dist[u][v]=min(dist[u][v],w);
        dist[v][u]=min(dist[v][u],w);
    }
    cir(i,0,n) dist[i][i]=0;
    cir(k,0,n) cir(i,0,n) cir(j,0,n){
        dist[i][j]=min(dist[i][j],dist[i][k]+dist[k][j]);
    }
    for(auto&ar:qx){
        if(ar.size()==2){
            const auto[u,v,w]=es[ar[1]];
            cir(i,0,n) cir(j,0,n) dist[i][j]=min({dist[i][j],dist[i][u]+dist[v][j]+w,dist[i][v]+dist[u][j]+w});
        }else{
            int u,v;tie(u,v)={ar[1],ar[2]};
            ans.push_back((dist[u][v]==_infl?-1:dist[u][v]));
        }
    }
    for(auto&i:views::reverse(ans)) cout<<i<<'\n';
    return 0;
}
