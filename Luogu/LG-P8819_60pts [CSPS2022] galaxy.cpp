#include<bits/stdc++.h>
#define cir(i,a,b) for(int i=a;i<b;++i)
using namespace std;
vector<unordered_set<int>> G;
vector<vector<int>> G2;
int lefts=0;
void Bu(int u,int v){
    if(G[u].count(v)) return;
    lefts+=(G[u].empty()?1:(G[u].size()==1?-1:0));
    G[u].insert(v);
}
void Bm(int u,int v){
    if(!G[u].count(v)) return;
    lefts+=(G[u].size()==2?1:(G[u].size()==1?-1:0));
    G[u].erase(v);
}
void Del(int u){
    for(auto&i:G2[u]) Bm(i,u);
}
void Rbu(int u){
    for(auto i:G2[u]) Bu(i,u);
}
int main(){
    ios::sync_with_stdio(false),cin.tie(0);
    int n,m;cin>>n>>m;G.resize(n+1);
    G2.resize(n+1);
    cir(i,0,m){
        int u,v;cin>>u>>v;
        G[u].insert(v);G2[v].push_back(u);
    }
    cir(i,1,n+1) lefts+=(G[i].size()==1);
    int q;cin>>q;
    while(q--){
        int d,a,b;cin>>d;
        switch(d){
            case 1:
                cin>>a>>b;Bm(a,b);break;
            case 2:
                cin>>a;Del(a);break;
            case 3:
                cin>>a>>b;Bu(a,b);break;
            default:
                cin>>a;Rbu(a);break;
        }
        cout<<(lefts==n?"YES":"NO")<<endl;
    }
    return 0;
}