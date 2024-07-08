#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
const int _inf=1e9+7;
vector<vector<int>> G;
int bfs(int n){
    queue<int> q;q.push(0);
    vector<int> D(n,_inf),vis(n);
    D[0]=0;vis[0]=true;
    while(!q.empty()){
        const auto u=q.front();q.pop();
        for(auto&i:G[u]) if(!vis[i]){
            q.push(i);vis[i]=true;
            D[i]=D[u]+1;
        }
    }
    return D[n-1];
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n;cin>>n;vector<int> a(n);
    for(auto&i:a) cin>>i;
    G.resize(n);
    unordered_map<int,int> pos;
    for(int i=n-1;~i;--i){
        if(pos.count(a[i])){
            G[i].push_back(pos[a[i]]);
        }
        pos[a[i]]=i;
        if(i<n-1) G[i].push_back(i+1);
        if(i) G[i].push_back(i-1);
    }
    cout<<bfs(n)<<'\n';
    return 0;
}
