#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
struct edge{int v,w;};
vector<vector<edge>> G;
const int _inf=1e9+7;
int spfa(int ux){
    vector<int> D(G.size(),_inf);
    deque<int> q;q.push_back(ux);D[ux]=0;
    while(!q.empty()){
        auto u=q.front(),w=D[u];q.pop_front();
        for(auto&[v,wi]:G[u]){
            if(D[v]<=w-wi) continue;
            D[v]=w-wi;
            if(q.empty()||D[v]<=D[q.front()])
                q.push_front(v);
            else
                q.push_back(v);
        }
    }
    return -*min_element(D.begin(),D.end());
}
int dist(int x,int y){return x>y?x-y:(x-y)*2;}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,m;cin>>n>>m;G.resize(n+1);
    vector<int> H(n+1);
    cir(i,1,n+1) cin>>H[i];
    cir(i,0,m){
        int u,v;cin>>u>>v;
        G[u].push_back({v,dist(H[u],H[v])});
        G[v].push_back({u,dist(H[v],H[u])});
    }
    cout<<spfa(1)<<'\n';
    return 0;
}
