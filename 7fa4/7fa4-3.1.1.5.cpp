#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
vector<vector<int>> G;
vector<int> vist;
void bfs(int u,int n){
    queue<int> q;q.push(u);
    vector<bool> inq(n+1);
    inq[u]=true;
    while(!q.empty()){
        auto f=q.front();q.pop();
        vist[f]++;
        for(auto&i:G[f]) if(!inq[i]){
            inq[i]=true;q.push(i);
        }
    }
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int k,n,m;cin>>k>>n>>m;
    G.resize(n+1);vist.resize(n+1);
    vector<int> s(k);
    for(auto&i:s) cin>>i;
    cir(i,0,m){
        int u,v;cin>>u>>v;
        G[u].push_back(v);
    }
    for(auto&i:s) bfs(i,n);
    int cnt=0;
    cir(i,1,n+1) cnt+=(vist[i]==k);
    cout<<cnt<<'\n';
    return 0;
}