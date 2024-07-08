#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
struct edge{int u,w;};
vector<vector<edge>> G;
const int _inf=1e9+7;
int bfs(int n,int k){
    vector<int> D(n+1,_inf),vis(n+1);
    deque<int> q;q.push_back(1);
    D[1]=0;
    while(!q.empty()){
        int f=q.front();q.pop_front();
        if(vis[f]) continue;
        for(auto&i:G[f]){
            bool b=(i.w>k);
            if((!vis[i.u])&&D[i.u]>D[f]+b)
                ((!b)?q.push_front(i.u):q.push_back(i.u)),D[i.u]=D[f]+b;
        }
    }
    return D[n];
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,m,k;cin>>n>>m>>k;G.resize(n+1);
    cir(i,0,m){
        int x,y,z;cin>>x>>y>>z;
        G[x].push_back({y,z});G[y].push_back({x,z});
    }
    int l=0,r=_inf,ans=-1;
    while(r>=l){
        int mid=(l+r)/2;
        bfs(n,mid)<=k?ans=mid,r=mid-1:l=mid+1;
    }
    cout<<ans<<endl;
    return 0;
}